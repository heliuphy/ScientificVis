//
// Created by 何柳 on 2020/3/10.
//
#include <vtkSmartPointer.h>
#include <iostream>
#include <vtkMetaImageReader.h>
#include <vtkImageCast.h>
#include <vtkPNGWriter.h>

using std::cout;
using std::endl;

int main(int argc, char **argv) {
    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();

    vtkSmartPointer<vtkImageCast> imageCast =
            vtkSmartPointer<vtkImageCast>::New();
    imageCast->SetInputConnection(reader->GetOutputPort());
    imageCast->SetOutputScalarTypeToUnsignedShort();
    imageCast->Update();

    vtkSmartPointer<vtkPNGWriter> writer =
            vtkSmartPointer<vtkPNGWriter>::New();
    writer->SetInputConnection(imageCast->GetOutputPort());
    writer->SetFileName(argv[2]);
    writer->Write();

    return EXIT_SUCCESS;

}

