//
// Created by 何柳 on 2020/3/24.
//

#include "generate3dByFIrstMethod.h"
#include "CircleDelete.h"

bool recordSpecialPlane(vtkImageData *_inputImageData, int _zIndex, vector<int> &_list) {

    auto _inputPointer = (unsigned char *) (_inputImageData->GetScalarPointer());

    int _dims[3];
    _inputImageData->GetDimensions(_dims);
    int _n = _dims[0] * _dims[1] * _dims[2];

    int count_0 = 0, count_1 = 0;

    for (int i = 0; i < _n; i++) {
        if (_inputPointer[i] == 1) {
            count_1++;
        } else {
            count_0++;
        }
    }
    assert(count_0 + count_1 == _n);

    if ((float) (count_1) / (float) (_n) > 0.16) {
        _list.push_back(_zIndex);
        return true;
    }

    return false;
}

int main() {

    //==========================================================================================
    //                        ==========       READ FILE        ==========
    //==========================================================================================
    // Reading 3d data plane and reference plane
    vtkSmartPointer<vtkMetaImageReader> d3reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    d3reader->SetFileName("/Users/heliu/data/MultiTImeStep/raw/Pressure_T0300.mhd");
    d3reader->Update();

    vtkSmartPointer<vtkMetaImageReader> referencePlaneReader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    referencePlaneReader->SetFileName("/Users/heliu/data/MultiTImeStep/reference/plane.mhd");
    referencePlaneReader->Update();


    //==========================================================================================
    //                  ==========       IMAGE DATA        ==========
    //==========================================================================================
    //  Prepare required data structures and allocates memory

    vtkSmartPointer<vtkImageData> d3InputImageData = d3reader->GetOutput();
    vtkSmartPointer<vtkImageData> referencePlaneImageData = referencePlaneReader->GetOutput();

    ImageOriginSpacingExtent referenceInfo;
    referenceInfo.setOrigin(referencePlaneImageData->GetOrigin());
    referenceInfo.setSpacing(referencePlaneImageData->GetSpacing());
    referenceInfo.setExtent(referencePlaneImageData->GetExtent());
    referenceInfo.setDimension(referencePlaneImageData->GetDimensions());

    // 3d outputImageData
    vtkSmartPointer<vtkImageData> outputImageData =
            vtkSmartPointer<vtkImageData>::New();
    outputImageData->SetOrigin(d3InputImageData->GetOrigin());
    outputImageData->SetSpacing(d3InputImageData->GetSpacing());
    outputImageData->SetExtent(d3InputImageData->GetExtent());
    outputImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    // Data structure for slicing
    // prepare a temp plane to save one slice
    vtkSmartPointer<vtkImageData> workingOriginalPlaneImageData =
            vtkSmartPointer<vtkImageData>::New();
    workingOriginalPlaneImageData->SetOrigin(referenceInfo.Origin);
    workingOriginalPlaneImageData->SetSpacing(referenceInfo.Spacing);
    workingOriginalPlaneImageData->SetExtent(referenceInfo.Extent);
    workingOriginalPlaneImageData->AllocateScalars(VTK_FLOAT, 1);


    // Data structure for canny
    vtkSmartPointer<vtkImageData> afterCannyImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterCannyImageData->SetOrigin(referenceInfo.Origin);
    afterCannyImageData->SetSpacing(referenceInfo.Spacing);
    afterCannyImageData->SetExtent(referenceInfo.Extent);
    afterCannyImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);


    vtkSmartPointer<vtkImageData> afterNeighborGrowImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterNeighborGrowImageData->SetOrigin(referenceInfo.Origin);
    afterNeighborGrowImageData->SetSpacing(referenceInfo.Spacing);
    afterNeighborGrowImageData->SetExtent(referenceInfo.Extent);
    afterNeighborGrowImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);


    vtkSmartPointer<vtkImageData> afterCircleDeleteImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterCircleDeleteImageData->SetOrigin(referenceInfo.Origin);
    afterCircleDeleteImageData->SetSpacing(referenceInfo.Spacing);
    afterCircleDeleteImageData->SetExtent(referenceInfo.Extent);
    afterCircleDeleteImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);


    vtkSmartPointer<vtkImageData> afterMultiply =
            vtkSmartPointer<vtkImageData>::New();
    afterMultiply->SetOrigin(referenceInfo.Origin);
    afterMultiply->SetSpacing(referenceInfo.Spacing);
    afterMultiply->SetExtent(referenceInfo.Extent);
    afterMultiply->AllocateScalars(VTK_UNSIGNED_CHAR, 1);


    vtkSmartPointer<vtkMetaImageWriter> writer =
            vtkSmartPointer<vtkMetaImageWriter>::New();

    //==========================================================================================
    //                  ==========       ALGORITHM        ==========
    //==========================================================================================

    // object for slicing a plane
    hlwImageSlice imageSlice;
    imageSlice.setInputImageData(d3InputImageData);
    imageSlice.setOutputImageData(workingOriginalPlaneImageData);
    imageSlice.setReferencePlaneInfo(&referenceInfo);
//    imageSlice.setSliceIndex(199);
//    imageSlice.computeSlicePlaneInformation();

    // object for canny
    CannyDetect cannyDetect;
    cannyDetect.setInputImageData(workingOriginalPlaneImageData);
    cannyDetect.setOutputImageData(afterCannyImageData);


    // object for neighbor growing


    CircleDelete circleDelete;


    PlaneNeighborGrowing neighborGrowing;
//    neighborGrowing.setNeighborDistance(3);


    hlwImageMath multiply255;

    //==========================================================================================
    //                        ==========       RUN        ==========
    //==========================================================================================
    // Z normal planes
    // 第一遍填充，完全按照普通情况处理
    // 并记录特殊面，以待后续处理
    vector<int> specialPlaneIndex;

    for (int i = 0; i < 400; i++) {

        cout << "Now doing " << i << "th Plane! " << endl;
        // 1. 切面
        imageSlice.setSliceIndex(i);
        imageSlice.computeSlicePlaneInformation();
        imageSlice.run();

        int thisSliceExtent[6];
        imageSlice.getSliceExtent(thisSliceExtent);

        // 2. Canny Detect
        cannyDetect.run();


        ///////

        double intersections[8];
        int numIntersection = 0;
        circleDelete.setInputImageData(afterCannyImageData);
        circleDelete.findAllIntersectionPoints(intersections, &numIntersection);
        cout << "intersection num : " << numIntersection << endl;

        if (numIntersection == 4) {
            // delete 2nd circle
            vector<int> circle;

            circleDelete.setInputImageData(afterCannyImageData);
            circleDelete.setOutputImageData(afterCircleDeleteImageData);
            circleDelete.findCircleOld(intersections[1], circle);
            circleDelete.setDeleteCircle(circle);
            circleDelete.run();

            neighborGrowing.setInputImageData(afterCircleDeleteImageData);
            neighborGrowing.setOutputImageData(afterNeighborGrowImageData);
            neighborGrowing.setMode(GROW_ON_ALL_IMAGE);
            neighborGrowing.run();

        } else if (numIntersection == 6) {
            // delete 2nd circle
            vector<int> circle;
            circleDelete.setInputImageData(afterCannyImageData);
            circleDelete.setOutputImageData(afterCircleDeleteImageData);
            circleDelete.findCircleOld(intersections[1], circle);
            circleDelete.setDeleteCircle(circle);
            circleDelete.run();

            neighborGrowing.setInputImageData(afterCircleDeleteImageData);
            neighborGrowing.setOutputImageData(afterNeighborGrowImageData);
            neighborGrowing.setMode(GROW_ON_ALL_IMAGE);
            neighborGrowing.run();

        } else if (numIntersection == 8) {

            vector<int> circle_1;
            vector<int> circle_2;


            circleDelete.setInputImageData(afterCannyImageData);
            circleDelete.setOutputImageData(afterCircleDeleteImageData);
            circleDelete.findCircleOld(intersections[1], circle_1);
            circleDelete.findCircleOld(intersections[3], circle_2);


            circle_1.reserve(circle_1.size() + circle_2.size());
            for (auto i : circle_2) {
                circle_1.push_back(i);
            }

            circleDelete.setDeleteCircle(circle_1);
            circleDelete.run();

            neighborGrowing.setInputImageData(afterCircleDeleteImageData);
            neighborGrowing.setOutputImageData(afterNeighborGrowImageData);
            neighborGrowing.setMode(GROW_ON_ALL_IMAGE);
            neighborGrowing.run();


        }

        auto planePointerOf3dOutputData = (unsigned char *) (outputImageData->GetScalarPointerForExtent(
                thisSliceExtent));
        auto afterNeighborGrowPointer = (unsigned char *) (afterNeighborGrowImageData->GetScalarPointer());

        int dims[3];
        afterNeighborGrowImageData->GetDimensions(dims);

        int n = dims[0] * dims[1] * dims[2];

        memcpy(planePointerOf3dOutputData, afterNeighborGrowPointer, n * sizeof(unsigned char));

        neighborGrowing.outputImageClear();
    }


    std::string _fileName;
    _fileName = "/Users/heliu/data/MultiTImeStep/result/time300/result.mhd";

    writer->SetInputData(outputImageData);
    writer->SetFileName(_fileName.c_str());
    writer->Write();


}



