//
// Created by 何柳 on 2020/3/24.
//

#include "hlwImageFill.h"
#include "CannyDetect.h"
#include "hlwImageMath.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkMetaImageWriter.h>
#include <vtkPNGWriter.h>

int main() {
    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName("/Users/heliu/temp/node-centered/Test/FIll-test.mhd");
    reader->Update();

    vtkSmartPointer<vtkMetaImageReader> reader2 =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader2->SetFileName("/Users/heliu/temp/node-centered/Test/Canny-test.mhd");
    reader2->Update();

    vtkSmartPointer<vtkImageData> outputImageData =
            vtkSmartPointer<vtkImageData>::New();
    outputImageData->SetOrigin(reader->GetOutput()->GetOrigin());
    outputImageData->SetSpacing(reader->GetOutput()->GetSpacing());
    outputImageData->SetExtent(reader->GetOutput()->GetExtent());
    outputImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    vtkSmartPointer<vtkImageData> afterSubImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterSubImageData->SetOrigin(reader->GetOutput()->GetOrigin());
    afterSubImageData->SetSpacing(reader->GetOutput()->GetSpacing());
    afterSubImageData->SetExtent(reader->GetOutput()->GetExtent());
    afterSubImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    hlwImageMath imageMath;
    imageMath.setInputImageData(reader->GetOutput());
    imageMath.setInputImageData2(reader2->GetOutput());
    imageMath.setOutputImageData(afterSubImageData);
    imageMath.setOperatorToSub();
    imageMath.run();

    hlwImageMath imageMath2;
    imageMath2.setInputImageData(afterSubImageData);
    imageMath2.setOutputImageData(outputImageData);
    imageMath2.setOperatorToMultiplyK(255);
    imageMath2.run();

    vtkSmartPointer<vtkPNGWriter> writer =
            vtkSmartPointer<vtkPNGWriter>::New();
    writer->SetFileName("/Users/heliu/temp/node-centered/Test/sub-test.png");
    writer->SetInputData(outputImageData);
    writer->Write();
}


