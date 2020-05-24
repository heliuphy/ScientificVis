//
// Created by 何柳 on 2020/3/26.
//
#include "CircleDelete.h"
#include "hlwImageMath.h"

#include <iostream>
#include <vtkMetaImageReader.h>
#include <vtkSmartPointer.h>
#include <vtkMetaImageWriter.h>
#include <PlaneNeighborGrowing.h>
#include <vtkPNGWriter.h>

using std::iostream;


int main() {
    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName("/Users/heliu/OneDrive/Data/node-centered/Test/Canny-test.mhd");
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

    vtkSmartPointer<vtkImageData> afterDeleteCircle2 =
            vtkSmartPointer<vtkImageData>::New();
    afterDeleteCircle2->SetOrigin(reader->GetOutput()->GetOrigin());
    afterDeleteCircle2->SetSpacing(reader->GetOutput()->GetSpacing());
    afterDeleteCircle2->SetExtent(reader->GetOutput()->GetExtent());
    afterDeleteCircle2->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

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
    vector<int> circle2;
    planeNeighborGrowing.findCircleOld(p[1], circle);
    planeNeighborGrowing.findCircleOld(p[3], circle2);


    CircleDelete circleDelete;
    circleDelete.setInputImageData(reader->GetOutput());
    circleDelete.setOutputImageData(afterDeleteCircle);
    circleDelete.setDeleteCircle(circle);
    circleDelete.run();

    CircleDelete circleDelete2;
    circleDelete2.setInputImageData(afterDeleteCircle);
    circleDelete2.setOutputImageData(afterDeleteCircle2);
    circleDelete2.setDeleteCircle(circle2);
    circleDelete2.run();

    hlwImageMath imageMath;
    imageMath.setInputImageData(afterDeleteCircle2);
    imageMath.setOutputImageData(outputImageData);
    imageMath.setOperatorToMultiplyK(255);
    imageMath.run();


    vtkSmartPointer<vtkPNGWriter> writer =
            vtkSmartPointer<vtkPNGWriter>::New();

    writer->SetFileName("/Users/heliu/OneDrive/Data/node-centered/Test/circleDelete-test.png");
    writer->SetInputData(outputImageData);
    writer->Write();
}

