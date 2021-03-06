//
// Created by 何柳 on 2020/3/24.
//

#include "hlwImageFill.h"
#include "CannyDetect.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkMetaImageWriter.h>

int main() {
    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName("/Users/heliu/temp/node-centered/Test/Canny-test.mhd");
    reader->Update();

    vtkSmartPointer<vtkImageData> outputImageData =
            vtkSmartPointer<vtkImageData>::New();
    outputImageData->SetOrigin(reader->GetOutput()->GetOrigin());
    outputImageData->SetSpacing(reader->GetOutput()->GetSpacing());
    outputImageData->SetExtent(reader->GetOutput()->GetExtent());
    outputImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    real_T points[2];

    hlwImageFill imageFillEx;
    imageFillEx.setInputImageData(reader->GetOutput());
    imageFillEx.setOutputImageData(outputImageData);
    imageFillEx.findPointIDToImfill(points, points + 1);
    imageFillEx.setFillPoints(points, 2);
    imageFillEx.run();

    vtkSmartPointer<vtkMetaImageWriter> writer =
            vtkSmartPointer<vtkMetaImageWriter>::New();

    writer->SetFileName("/Users/heliu/temp/node-centered/Test/FIll-test.mhd");
    writer->SetInputData(outputImageData);
    writer->Write();
}


