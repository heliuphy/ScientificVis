//
// Created by 何柳 on 2020/3/23.
//

#include "PlaneNeighborGrowing.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkMetaImageWriter.h>
#include <hlwImageFill.h>

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

    double p[8];
    // Circle 1
    std::vector<int> l1;
    // Circle 2
    std::vector<int> l2;

    int edgeNum;

    hlwImageFill imageFill;
    imageFill.setInputImageData(reader->GetOutput());
    imageFill.findAllIntersectionPoints(p, &edgeNum);

    PlaneNeighborGrowing neighborGrowing;
    neighborGrowing.setInputImageData(reader->GetOutput());
    neighborGrowing.setOutputImageData(outputImageData);
    neighborGrowing.computePlaneSize();
    neighborGrowing.computeElementSize();
    neighborGrowing.findCircle(p[0], l1);
    neighborGrowing.findCircle(p[2], l2);

    l1.reserve(l1.size() + l2.size());
    for (auto i : l2) {
        l1.push_back(i);
    }


    neighborGrowing.setMode(GROW_ON_CIRCLE);
    neighborGrowing.setCirclePointsVector(&l1);
    neighborGrowing.run();


    vtkSmartPointer<vtkMetaImageWriter> writer =
            vtkSmartPointer<vtkMetaImageWriter>::New();

    writer->SetFileName("/Users/heliu/temp/node-centered/Test/neighbor-2.mhd");
    writer->SetInputData(outputImageData);
    writer->Write();
}

