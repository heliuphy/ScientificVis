//
// Created by 何柳 on 2020/3/24.
//

#include "generate3dByFIrstMethod.h"

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
    d3reader->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/volume800Meta.mhd");
    d3reader->Update();

    vtkSmartPointer<vtkMetaImageReader> referencePlaneReader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    referencePlaneReader->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/output/plane.mhd");
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


    // Data structure for imagefill

    vtkSmartPointer<vtkImageData> afterFillImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterFillImageData->SetOrigin(referenceInfo.Origin);
    afterFillImageData->SetSpacing(referenceInfo.Spacing);
    afterFillImageData->SetExtent(referenceInfo.Extent);
    afterFillImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    // Data structure for sub

    vtkSmartPointer<vtkImageData> afterSubImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterSubImageData->SetOrigin(referenceInfo.Origin);
    afterSubImageData->SetSpacing(referenceInfo.Spacing);
    afterSubImageData->SetExtent(referenceInfo.Extent);
    afterSubImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);


    vtkSmartPointer<vtkImageData> afterNeighborGrow =
            vtkSmartPointer<vtkImageData>::New();
    afterNeighborGrow->SetOrigin(referenceInfo.Origin);
    afterNeighborGrow->SetSpacing(referenceInfo.Spacing);
    afterNeighborGrow->SetExtent(referenceInfo.Extent);
    afterNeighborGrow->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

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


    // object for ImageFill
    real_T points[2];

    hlwImageFill imageFill;
    imageFill.setInputImageData(afterCannyImageData);
    imageFill.setOutputImageData(afterFillImageData);


    // object for sub
    hlwImageMath imageSub;
    imageSub.setInputImageData(afterFillImageData);
    imageSub.setInputImageData2(afterCannyImageData);
    imageSub.setOutputImageData(afterSubImageData);
    imageSub.setOperatorToSub();


    // object for neighbor growing
    PlaneNeighborGrowing neighborGrowing;


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


        // 3. Image Fill , record special planes and put them to outputImageData
        imageFill.findPointIDToImfill(points, points + 1);
        imageFill.setFillPoints(points, 2);
        imageFill.run();

        // 4. deal with special planes and put them to outputImageData
        // 4.1 determine whether this plane is special or not
        bool thisPlaneIsSpecial = recordSpecialPlane(afterFillImageData, i, specialPlaneIndex);

        // case by case
        if (!thisPlaneIsSpecial) {
            //  normal plane
            auto planePointerOf3dOutputData = (unsigned char *) (outputImageData->GetScalarPointerForExtent(
                    thisSliceExtent));

            imageSub.run();

            auto afterSubPointer = (unsigned char *) (afterSubImageData->GetScalarPointer());

            int dims[3];
            afterSubImageData->GetDimensions(dims);

            int n = dims[0] * dims[1] * dims[2];

//            memcpy(planePointerOf3dOutputData, afterSubPointer, n * sizeof(unsigned char));

            multiply255.setInputImageData(afterSubImageData);
            multiply255.setOutputImageData(afterMultiply);
            multiply255.setOperatorToMultiplyK(255);
            multiply255.run();

            std::string _path;
            std::string _fileName;
            _path = "/Users/heliu/temp/node-centered/step6/";
            _fileName = _path + std::to_string(i) + ".png";

            writer->SetInputData(afterMultiply);
            writer->SetFileName(_fileName.c_str());
            writer->Write();

        } else {
            // special plane
            neighborGrowing.setInputImageData(afterCannyImageData);
            neighborGrowing.setOutputImageData(afterNeighborGrow);
            neighborGrowing.setNeighborDistance(3);
            neighborGrowing.run();

            auto planePointerOf3dOutputData = (unsigned char *) (outputImageData->GetScalarPointerForExtent(
                    thisSliceExtent));

            auto afterNeighborGrowPointer = (unsigned char *) (afterNeighborGrow->GetScalarPointer());

            int dims[3];
            afterNeighborGrow->GetDimensions(dims);
            int n = dims[0] * dims[1] * dims[2];

//            memcpy(planePointerOf3dOutputData, afterNeighborGrowPointer, n * sizeof(unsigned char));

            multiply255.setInputImageData(afterNeighborGrow);
            multiply255.setOutputImageData(afterMultiply);
            multiply255.setOperatorToMultiplyK(255);
            multiply255.run();

            std::string _path;
            std::string _fileName;
            _path = "/Users/heliu/temp/node-centered/step6/";
            _fileName = _path + std::to_string(i) + ".png";

            writer->SetInputData(afterMultiply);
            writer->SetFileName(_fileName.c_str());
            writer->Write();
        }
    }

    cout << "Special planes are : " << endl;

    for (auto i : specialPlaneIndex) {
        cout << i << " ";
    }

    cout << endl;

}



