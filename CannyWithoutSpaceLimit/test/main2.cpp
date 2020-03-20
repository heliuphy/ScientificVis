
#include "rt_nonfinite.h"
#include "CannyAutoThres_X.h"
#include "CannyAutoThres_X_terminate.h"
#include "CannyAutoThres_X_emxAPI.h"
#include "CannyAutoThres_X_initialize.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <iostream>
#include <vtkMetaImageReader.h>
#include <vtkMetaImageWriter.h>
#include <vtkPNGWriter.h>

using std::cout;
using std::endl;


int main(int, const char *const[]) {

    CannyAutoThres_X_initialize();

    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/output/plane_X.mhd");
    reader->Update();

    vtkSmartPointer<vtkImageData> inputImageData = reader->GetOutput();

    auto inputPointer = (float *) (inputImageData->GetScalarPointer());

    emxArray_boolean_T *outputImage;
    emxArray_real32_T *inputImage;

    emxInitArray_boolean_T(&outputImage, 2);
    emxInitArray_real32_T(&inputImage, 2);

    inputImage->data = inputPointer;
    inputImage->size[0] = 800;
    inputImage->size[1] = 400;
    inputImage->allocatedSize = inputImage->size[0] * inputImage->size[1];
    inputImage->canFreeData = false;

    vtkSmartPointer<vtkImageData> outputImageData =
            vtkSmartPointer<vtkImageData>::New();
    outputImageData->SetOrigin(inputImageData->GetOrigin());
    outputImageData->SetSpacing(inputImageData->GetSpacing());
    outputImageData->SetExtent(inputImageData->GetExtent());
    outputImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    auto outputPointer = (boolean_T *) (outputImageData->GetScalarPointer());
    outputImage->data = outputPointer;
    outputImage->size[0] = 800;
    outputImage->size[1] = 400;
    outputImage->allocatedSize = outputImage->size[0] * outputImage->size[1];
    outputImage->canFreeData = false;

    CannyAutoThres_X(inputImage, outputImage);

    vtkSmartPointer<vtkImageData> multiply255 =
        vtkSmartPointer<vtkImageData>::New();
    multiply255->SetOrigin(inputImageData->GetOrigin());
    multiply255->SetSpacing(inputImageData->GetSpacing());

    int originalExtent[6];
    inputImageData->GetExtent(originalExtent);
    int newExtent[6] = {0};
    newExtent[0] = originalExtent[2];
    newExtent[1] = originalExtent[3];
    newExtent[2] = originalExtent[4];
    newExtent[3] = originalExtent[5];

    multiply255->SetExtent(newExtent);
    multiply255->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    auto pm = (unsigned char *)(multiply255->GetScalarPointer());
    auto po = (boolean_T *)(outputImageData->GetScalarPointer());

    for (int i = 0; i < outputImage->allocatedSize; i++) {
        pm[i] = po[i] * 255;
    }

//    vtkSmartPointer<vtkMetaImageWriter> writer =
//        vtkSmartPointer<vtkMetaImageWriter>::New();
//    writer->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/output/Canny_X_plane.mhd");
//    writer->SetInputData(outputImageData);
//    writer->Write();

    vtkSmartPointer<vtkPNGWriter> writer =
            vtkSmartPointer<vtkPNGWriter>::New();
    writer->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/output/Canny_X_plane.png");
    writer->SetInputData(multiply255);
    writer->Write();

//    inputImage->canFreeData = true;
//    outputImage->canFreeData = true;
//
    // Call the entry-point 'CannyAutoThres_X'.
//    emxDestroyArray_boolean_T(outputImage);
//    emxDestroyArray_real32_T(inputImage);


    // Terminate the application.
    // You do not need to do this more than one time.
    CannyAutoThres_X_terminate();
    return 0;
}

