//
// Created by 何柳 on 2020/3/23.
//
#include "AlgoBase.h"

int main() {

//    int size0 = 800;
//    int size1 = 400;

//    vtkSmartPointer<vtkMetaImageReader> d3reader =
//            vtkSmartPointer<vtkMetaImageReader>::New();
//    d3reader->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/volume800Meta.mhd");
//    d3reader->Update();

    vtkSmartPointer<vtkMetaImageReader> planeReader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    planeReader->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/output/plane.mhd");
    planeReader->Update();

//    vtkSmartPointer<vtkImageData> input3DImageData = d3reader->GetOutput();
    vtkSmartPointer<vtkImageData> planeImageData = planeReader->GetOutput();

    int zStart = 0;
    int zEnd = 399;
    int planeSpacing = 1;

    AlgoBase algoBase(zStart,
                      zEnd,
                      planeSpacing,
                      planeImageData,
                      nullptr);

    algoBase.setToCannyImageData(planeImageData);

    vtkSmartPointer<vtkImageData> afterCannyImageData =
            vtkSmartPointer<vtkImageData>::New();
    algoBase.setAfterCannyImageData(afterCannyImageData);

    vtkSmartPointer<vtkImageData> afterFillImageData
            = vtkSmartPointer<vtkImageData>::New();
    algoBase.setAfterFillImageData(afterFillImageData);

    vtkSmartPointer<vtkImageData> afterSubImageData =
            vtkSmartPointer<vtkImageData>::New();
    algoBase.setAfterSubImageData(afterSubImageData);

    vtkSmartPointer<vtkImageData> multiply255 =
            vtkSmartPointer<vtkImageData>::New();
    algoBase.setMultiply255(multiply255);

    algoBase.cannyDetect();

    double pID[2] = {0};
    algoBase.findPointIDToImfill(pID, pID + 1);
    cout << "p1 " << pID[0] << " p2 " << pID[1] << endl;

    algoBase.doImageFill(pID[0], pID[1]);

    algoBase.twoImagesSub(afterFillImageData, afterCannyImageData, afterSubImageData);

    algoBase.booleanImageMultiplyByK(afterFillImageData, multiply255, 255);

//    vtkSmartPointer<vtkPNGWriter> writer =
//            vtkSmartPointer<vtkPNGWriter>::New();
//    writer->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/output/plane_AlgoBase.png");
//    writer->SetInputData(multiply255);
    vtkSmartPointer<vtkMetaImageWriter> writer =
            vtkSmartPointer<vtkMetaImageWriter>::New();
    writer->SetInputData(afterSubImageData);
    writer->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/output/plane_AlgoBase.mhd");
    writer->Write();


}
