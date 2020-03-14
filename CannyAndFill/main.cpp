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

    // Save file
    vtkSmartPointer<vtkMetaImageWriter> writer =
            vtkSmartPointer<vtkMetaImageWriter>::New();
    writer->SetFileName(argv[2]);
    writer->SetInputData(outputImageData);
    writer->Write();

//    vtkSmartPointer<vtkPNGWriter> writer =
//            vtkSmartPointer<vtkPNGWriter>::New();
//    writer->SetFileName(argv[2]);
//    writer->SetInputData(outputImageData);
//    writer->Write();
    // Clean
    ImageFill_terminate();
    CannyAutoThres_terminate();
    return 0;
}
