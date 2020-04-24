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
    d3reader->SetFileName("/users/heliu/onedrive/data/node-centered/step-1-reslice/volume800Meta.mhd");
    d3reader->Update();

    vtkSmartPointer<vtkMetaImageReader> referencePlaneReader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    referencePlaneReader->SetFileName("/users/heliu/onedrive/data/node-centered/step-1-reslice/output/plane.mhd");
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


    vtkSmartPointer<vtkPNGWriter> writer =
            vtkSmartPointer<vtkPNGWriter>::New();

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
    neighborGrowing.setNeighborDistance(3);


    hlwImageMath multiply255;

    //==========================================================================================
    //                        ==========       RUN        ==========
    //==========================================================================================
    // Z normal planes
    // 第一遍填充，完全按照普通情况处理
    // 并记录特殊面，以待后续处理
    vector<int> specialPlaneIndex;

    for (int i = 0; i < 400; i++) {


        if (i == 19 || i == 145 || i == 254 || i == 380) {

            cout << endl;
            cout << "Outer circle " << endl;
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
            cout << " i == " << i << endl;
            cout << "intersection num : " << numIntersection << endl;
        }


        if (i == 67 || i == 125 || i == 182 || i == 191) {

            cout << endl;
            cout << "Inner circle " << endl;
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
            cout << " i == " << i << endl;
            cout << "intersection num : " << numIntersection << endl;
        }
    }


}



