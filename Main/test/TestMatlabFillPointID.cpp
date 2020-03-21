//
// Created by 何柳 on 2020/3/15.
//

#include <vtkSmartPointer.h>
#include <vtkMetaImageReader.h>
#include "ImageFill.h"
#include "ImageFill_initialize.h"
#include "ImageFill_terminate.h"
#include <vtkImageData.h>
#include <vtkMetaImageWriter.h>

int main(int argc, char **argv) {
    ImageFill_initialize();

    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();

    vtkSmartPointer<vtkImageData> outputImage =
            vtkSmartPointer<vtkImageData>::New();
    outputImage->SetExtent(reader->GetOutput()->GetExtent());
    outputImage->SetOrigin(reader->GetOutput()->GetOrigin());
    outputImage->SetSpacing(reader->GetOutput()->GetSpacing());
    outputImage->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    auto inputImagePointer = static_cast<boolean_T *>(reader->GetOutput()->GetScalarPointer());
    auto outputImagePointer = static_cast<boolean_T *>(outputImage->GetScalarPointer());

    double p1 = 2390;
    double p2 = 2391;

    ImageFill(inputImagePointer, p1, p2, outputImagePointer);


    vtkSmartPointer<vtkMetaImageWriter> writer =
            vtkSmartPointer<vtkMetaImageWriter>::New();
    writer->SetFileName(argv[2]);
    writer->SetInputData(outputImage);
    writer->Write();


    ImageFill_terminate();
}