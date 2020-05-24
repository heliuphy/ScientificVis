//
// Created by 何柳 on 2020/3/24.
//

#include "generate3dByFIrstMethod.h"

int main() {

    //==========================================================================================
    //                        ==========       READ FILE        ==========
    //==========================================================================================
    // Reading 3d data plane and reference plane
    vtkSmartPointer<vtkMetaImageReader> d3reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    d3reader->SetFileName("/Users/heliu/data/MultiTImeStep/raw/Pressure_T0900.mhd");
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


    hlwImageMath multiply255;

    //==========================================================================================
    //                        ==========       RUN        ==========
    //==========================================================================================


    // Z normal planes

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


        multiply255.setInputImageData(afterCannyImageData);
        multiply255.setOutputImageData(afterMultiply);
        multiply255.setOperatorToMultiplyK(255);
        multiply255.run();

        std::string _path;
        std::string _fileName;
        _path = "/Users/heliu/data/MultiTImeStep/canny400/time900/";
        _fileName = _path + std::to_string(i) + ".png";

        writer->SetInputData(afterMultiply);
        writer->SetFileName(_fileName.c_str());
        writer->Write();


    }

    cout << endl;

}



