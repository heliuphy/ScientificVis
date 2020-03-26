//
// Created by 何柳 on 2020/3/26.
//
#include "CircleDelete.h"

#include <iostream>
#include <vtkMetaImageReader.h>
#include <vtkSmartPointer.h>
#include <vtkMetaImageWriter.h>
#include <PlaneNeighborGrowing.h>

using std::iostream;


int main() {
    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName("/Users/heliu/temp/node-centered/Test/Canny-test.mhd");
    reader->Update();

    vtkSmartPointer<vtkImageData> afterNeighborGrowImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterNeighborGrowImageData->SetOrigin(reader->GetOutput()->GetOrigin());
    afterNeighborGrowImageData->SetSpacing(reader->GetOutput()->GetSpacing());
    afterNeighborGrowImageData->SetExtent(reader->GetOutput()->GetExtent());
    afterNeighborGrowImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);


    vtkSmartPointer<vtkImageData> afterDeleteCircle =
            vtkSmartPointer<vtkImageData>::New();
    afterDeleteCircle->SetOrigin(reader->GetOutput()->GetOrigin());
    afterDeleteCircle->SetSpacing(reader->GetOutput()->GetSpacing());
    afterDeleteCircle->SetExtent(reader->GetOutput()->GetExtent());
    afterDeleteCircle->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    vtkSmartPointer<vtkImageData> outputImageData =
            vtkSmartPointer<vtkImageData>::New();
    outputImageData->SetOrigin(reader->GetOutput()->GetOrigin());
    outputImageData->SetSpacing(reader->GetOutput()->GetSpacing());
    outputImageData->SetExtent(reader->GetOutput()->GetExtent());
    outputImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);


    PlaneNeighborGrowing planeNeighborGrowing;
    planeNeighborGrowing.setInputImageData(reader->GetOutput());
    planeNeighborGrowing.computePlaneSize();
    planeNeighborGrowing.computeElementSize();
    double p[8];
    int numP;
    planeNeighborGrowing.findAllIntersectionPoints(p, &numP);
    vector<int> circle;
    planeNeighborGrowing.findCircle(p[0], circle);


    CircleDelete circleDelete;
    circleDelete.setInputImageData(reader->GetOutput());
    circleDelete.setOutputImageData(afterDeleteCircle);
    circleDelete.setDeleteCircle(circle);
    circleDelete.run();

    vtkSmartPointer<vtkMetaImageWriter> writer =
            vtkSmartPointer<vtkMetaImageWriter>::New();

    writer->SetFileName("/Users/heliu/temp/node-centered/Test/circleDelete-test.mhd");
    writer->SetInputData(afterDeleteCircle);
    writer->Write();
}

