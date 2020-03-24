//
// Created by 何柳 on 2020/3/23.
//

#include "PlaneNeighborGrowing.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkMetaImageWriter.h>

int main() {
    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/output/CannyAutoPlane.mhd");
    reader->Update();

    vtkSmartPointer<vtkImageData> outputImageData =
        vtkSmartPointer<vtkImageData>::New();
    outputImageData->SetOrigin(reader->GetOutput()->GetOrigin());
    outputImageData->SetSpacing(reader->GetOutput()->GetSpacing());
    outputImageData->SetExtent(reader->GetOutput()->GetExtent());
    outputImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    PlaneNeighborGrowing neighborGrowing(2);
    neighborGrowing.setInputImageData(reader->GetOutput());
    neighborGrowing.setOutputImageData(outputImageData);
    neighborGrowing.computePlaneSize();
    neighborGrowing.computeElementSize();
    neighborGrowing.run();

   vtkSmartPointer<vtkMetaImageWriter> writer =
       vtkSmartPointer<vtkMetaImageWriter>::New();

    writer->SetFileName("/Users/heliu/temp/node-centered/Test/neighbor.mhd");
    writer->SetInputData(outputImageData);
    writer->Write();
}

