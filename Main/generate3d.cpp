//
// Created by 何柳 on 2020/3/24.
//

#include <vtkPNGWriter.h>
#include "generate3d.h"

int main() {
    // Reading 3d data plane and reference plane
    vtkSmartPointer<vtkMetaImageReader> d3reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    d3reader->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/volume800Meta.mhd");
    d3reader->Update();

    vtkSmartPointer<vtkMetaImageReader> referencePlaneReader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    referencePlaneReader->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/output/plane.mhd");
    referencePlaneReader->Update();


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

    vtkSmartPointer<vtkImageData> afterFillImageData=
            vtkSmartPointer<vtkImageData>::New();
    afterFillImageData->SetOrigin(referenceInfo.Origin);
    afterFillImageData->SetSpacing(referenceInfo.Spacing);
    afterFillImageData->SetExtent(referenceInfo.Extent);
    afterFillImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    // Data structure for sub

    vtkSmartPointer<vtkImageData> afterSubImageData=
            vtkSmartPointer<vtkImageData>::New();
    afterSubImageData->SetOrigin(referenceInfo.Origin);
    afterSubImageData->SetSpacing(referenceInfo.Spacing);
    afterSubImageData->SetExtent(referenceInfo.Extent);
    afterSubImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);


    vtkSmartPointer<vtkImageData> afterMultiply =
        vtkSmartPointer<vtkImageData>::New();
    afterMultiply->SetOrigin(referenceInfo.Origin);
    afterMultiply->SetSpacing(referenceInfo.Spacing);
    afterMultiply->SetExtent(referenceInfo.Extent);
    afterMultiply->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    // ==========================================================================================
    //
    // ==========================================================================================

    // object for slicing a plane
    hlwImageSlice imageSlice;
    imageSlice.setInputImageData(d3InputImageData);
    imageSlice.setOutputImageData(workingOriginalPlaneImageData);
    imageSlice.setReferencePlaneInfo(&referenceInfo);
    imageSlice.setSliceIndex(199);
    imageSlice.computeSlicePlaneInformation();

    // object for canny

    CannyDetect cannyDetect;
    cannyDetect.setInputImageData(workingOriginalPlaneImageData);
    cannyDetect.setOutputImageData(afterCannyImageData);


    // object for ImageFill

    real_T points[2];

    hlwImageFill imageFill;
    imageFill.setInputImageData(afterCannyImageData);
    imageFill.setOutputImageData(afterFillImageData);
    imageFill.findPointIDToImfill(points, points + 1);
    imageFill.setFillPoints(points, 2);


    // object for sub
    hlwImageMath imageSub;
    imageSub.setInputImageData(afterFillImageData);
    imageSub.setInputImageData2(afterCannyImageData);
    imageSub.setOutputImageData(afterSubImageData);
    imageSub.setOperatorToSub();

    hlwImageMath multiply255;
    multiply255.setInputImageData(afterCannyImageData);
    multiply255.setOutputImageData(afterMultiply);
    multiply255.setOperatorToMultiplyK(255);
    multiply255.array1MultiplyByK();

    //==========================================================================================
    //                        ==========       RUN        ==========
    //==========================================================================================

    imageSlice.run();
    cannyDetect.run();
    imageFill.run();
    imageSub.run();
    multiply255.run();


    vtkSmartPointer<vtkPNGWriter> writer =
        vtkSmartPointer<vtkPNGWriter>::New();
    writer->SetFileName("/Users/heliu/temp/node-centered/Test/multi-test.png");
    writer->SetInputData(afterMultiply);
    writer->Write();

    // Z normal planes
    // 第一遍填充，完全按照普通情况处理
    // 并记录特殊面，以待后续处理
    vector<int> specialPlaneIndex;

    for (int i = 0; i < 400; i++) {
        // 1. 切面
        // 2. Canny Detect
        // 3. Image Fill , record special planes and put them to outputImageData
        // 4. deal with special planes and put them to outputImageData
    }

}
