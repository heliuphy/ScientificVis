//
// Created by 何柳 on 2020/3/14.
//
#include "ImageFill_types.h"
#include "ImageFill.h"
#include "ImageFill_terminate.h"
#include "ImageFill_initialize.h"
#include "CannyAutoThres.h"
#include "CannyAutoThres_terminate.h"
#include "CannyAutoThres_initialize.h"
#include "rtwtypes.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkPNGWriter.h>
#include <vtkMetaImageWriter.h>
#include <vtkImageMathematics.h>
#include "utils/HlwUtils.h"

void findPointIDToImfill(vtkImageData *planeImageData, double *p1, double *p2) {
    int planeExtent[6];
    planeImageData->GetExtent(planeExtent);

    int horizontalLineExtent[6] = {0, 0, 0, 0, 0, 0};
    horizontalLineExtent[1] = planeExtent[1];
    horizontalLineExtent[2] = (planeExtent[3] - planeExtent[2]) / 2;
    horizontalLineExtent[3] = horizontalLineExtent[2];
    horizontalLineExtent[4] = planeExtent[4];
    horizontalLineExtent[5] = planeExtent[5];

    printArray<int>(planeExtent, 6, "planeExtent");
    printArray<int>(horizontalLineExtent, 6, "horizonExtent");

    

}

int main(int argc, char **argv) {
    // Initialize
    CannyAutoThres_initialize();
    ImageFill_initialize();

    // Main program logic
    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();

    vtkSmartPointer<vtkImageData> inputImageData = reader->GetOutput();

    vtkSmartPointer<vtkImageData> afterCannyImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterCannyImageData->SetOrigin(inputImageData->GetOrigin());
    afterCannyImageData->SetExtent(inputImageData->GetExtent());
    afterCannyImageData->SetSpacing(inputImageData->GetSpacing());
    afterCannyImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);


    vtkSmartPointer<vtkImageData> outputImageData =
            vtkSmartPointer<vtkImageData>::New();
    outputImageData->SetOrigin(inputImageData->GetOrigin());
    outputImageData->SetExtent(inputImageData->GetExtent());
    outputImageData->SetSpacing(inputImageData->GetSpacing());
    outputImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    auto inputDataPointer = (float *) (inputImageData->GetScalarPointer());
    auto afterCannyDataPointer = (boolean_T *) (afterCannyImageData->GetScalarPointer());
    auto outputDataPointer = (boolean_T *) (outputImageData->GetScalarPointer());

    // Canny Edge Detection
    CannyAutoThres(inputDataPointer, afterCannyDataPointer);
    // Fill
    double p1 = 161207, p2 = 204410;
    ImageFill(afterCannyDataPointer, p1, p2, outputDataPointer);

    // 计算两图之差
    vtkSmartPointer<vtkImageMathematics> imageMath =
            vtkSmartPointer<vtkImageMathematics>::New();
    imageMath->SetInput1Data(outputImageData);
    imageMath->SetInput2Data(afterCannyImageData);
    imageMath->SetOperationToSubtract();
    imageMath->Update();

    double *pointID1 = nullptr, *pointID2 = nullptr;
    findPointIDToImfill(afterCannyImageData, pointID1, pointID2);

    // Save file
//    vtkSmartPointer<vtkMetaImageWriter> writer =
//            vtkSmartPointer<vtkMetaImageWriter>::New();
//    writer->SetFileName(argv[2]);
////    writer->SetInputData(outputImageData);
//    writer->SetInputConnection(imageMath->GetOutputPort());
//    writer->Write();


    // Clean
    ImageFill_terminate();
    CannyAutoThres_terminate();
    return 0;
}
