
//
// Created by 何柳 on 2020/3/23.
//

#include "CannyDetect.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkMetaImageWriter.h>

int main() {
    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/output/plane.mhd");
    reader->Update();

    vtkSmartPointer<vtkImageData> outputImageData =
            vtkSmartPointer<vtkImageData>::New();
    outputImageData->SetOrigin(reader->GetOutput()->GetOrigin());
    outputImageData->SetSpacing(reader->GetOutput()->GetSpacing());
    outputImageData->SetExtent(reader->GetOutput()->GetExtent());
    outputImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    CannyDetect cannyDetect;
    cannyDetect.setInputImageData(reader->GetOutput());
    cannyDetect.setOutputImageData(outputImageData);
    cannyDetect.run();

    vtkSmartPointer<vtkMetaImageWriter> writer =
            vtkSmartPointer<vtkMetaImageWriter>::New();

    writer->SetFileName("/Users/heliu/temp/node-centered/Test/Canny-test.mhd");
    writer->SetInputData(outputImageData);
    writer->Write();
}


