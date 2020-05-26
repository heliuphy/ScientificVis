//
// Created by 何柳 on 2020/3/24.
//

#include "generate3dByFIrstMethod.h"
#include "CircleDelete.h"
#include "SliceTypeDetector.h"
#include "DrawCircles.h"

int main() {

    //==========================================================================================
    //                        ==========       READ FILE        ==========
    //==========================================================================================
    // Reading 3d data plane and reference plane
    // /Users/heliu/OneDrive/Data/node-centered
    vtkSmartPointer<vtkMetaImageReader> d3reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    d3reader->SetFileName("/Users/heliu/data/MultiTImeStep/raw/Pressure_T1200.mhd");
    d3reader->Update();

    vtkSmartPointer<vtkMetaImageReader> referencePlaneReader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    referencePlaneReader->SetFileName("/Users/heliu/data/MultiTImeStep/reference/plane.mhd");
    referencePlaneReader->Update();


    //==========================================================================================
    //                  ==========       IMAGE DATA        ==========
    //==========================================================================================
    //  Prepare required data structures and allocates memory

    vtkSmartPointer<vtkImageData> d3InputImageData = d3reader->GetOutput();
    vtkSmartPointer<vtkImageData> referencePlaneImageData = referencePlaneReader->GetOutput();

    ImageOriginSpacingExtent referenceInfo;
    referenceInfo.setOrigin(referencePlaneImageData->GetOrigin());
    referenceInfo.setSpacing(referencePlaneImageData->GetSpacing());
    referenceInfo.setExtent(referencePlaneImageData->GetExtent());
    referenceInfo.setDimension(referencePlaneImageData->GetDimensions());

    // 3d outputImageData
    vtkSmartPointer<vtkImageData> outputImageData =
            vtkSmartPointer<vtkImageData>::New();
    outputImageData->SetOrigin(d3InputImageData->GetOrigin());
    outputImageData->SetSpacing(d3InputImageData->GetSpacing());
    outputImageData->SetExtent(d3InputImageData->GetExtent());
    outputImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    // Data structure for slicing
    // prepare a temp plane to save one slice
    vtkSmartPointer<vtkImageData> workingOriginalPlaneImageData =
            vtkSmartPointer<vtkImageData>::New();
    workingOriginalPlaneImageData->SetOrigin(referenceInfo.Origin);
    workingOriginalPlaneImageData->SetSpacing(referenceInfo.Spacing);
    workingOriginalPlaneImageData->SetExtent(referenceInfo.Extent);
    workingOriginalPlaneImageData->AllocateScalars(VTK_FLOAT, 1);


    // Data structure for canny
    vtkSmartPointer<vtkImageData> afterCannyImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterCannyImageData->SetOrigin(referenceInfo.Origin);
    afterCannyImageData->SetSpacing(referenceInfo.Spacing);
    afterCannyImageData->SetExtent(referenceInfo.Extent);
    afterCannyImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);


    vtkSmartPointer<vtkImageData> afterNeighborGrowImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterNeighborGrowImageData->SetOrigin(referenceInfo.Origin);
    afterNeighborGrowImageData->SetSpacing(referenceInfo.Spacing);
    afterNeighborGrowImageData->SetExtent(referenceInfo.Extent);
    afterNeighborGrowImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);


    vtkSmartPointer<vtkImageData> afterDrawCircleImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterDrawCircleImageData->SetOrigin(referenceInfo.Origin);
    afterDrawCircleImageData->SetSpacing(referenceInfo.Spacing);
    afterDrawCircleImageData->SetExtent(referenceInfo.Extent);
    afterDrawCircleImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);


    vtkSmartPointer<vtkImageData> afterMultiply =
            vtkSmartPointer<vtkImageData>::New();
    afterMultiply->SetOrigin(referenceInfo.Origin);
    afterMultiply->SetSpacing(referenceInfo.Spacing);
    afterMultiply->SetExtent(referenceInfo.Extent);
    afterMultiply->AllocateScalars(VTK_UNSIGNED_CHAR, 1);


    vtkSmartPointer<vtkPNGWriter> writer =
            vtkSmartPointer<vtkPNGWriter>::New();

    //==========================================================================================
    //                  ==========       ALGORITHM        ==========
    //==========================================================================================

    // object for slicing a plane
    hlwImageSlice imageSlice;
    imageSlice.setInputImageData(d3InputImageData);
    imageSlice.setOutputImageData(workingOriginalPlaneImageData);
    imageSlice.setReferencePlaneInfo(&referenceInfo);

    // object for canny
    CannyDetect cannyDetect;
    cannyDetect.setInputImageData(workingOriginalPlaneImageData);
    cannyDetect.setOutputImageData(afterCannyImageData);

    // object for detecting edge types
    SliceTypeDetector sliceTypeDetector;

    DrawCircles drawCircles;

    PlaneNeighborGrowing neighborGrowing;
    neighborGrowing.setNeighborDistance(3);

    hlwImageMath multiply255;

    //==========================================================================================
    //                        ==========       RUN        ==========
    //==========================================================================================

    for (int i = 0; i < 400; i++) {
//    for (int i = 58; i < 80; i++) {

        cout << "Now doing " << i << "th Plane! " << endl;
        // 1. 切面
        imageSlice.setSliceIndex(i);
        imageSlice.computeSlicePlaneInformation();
        imageSlice.run();

        int thisSliceExtent[6];
        imageSlice.getSliceExtent(thisSliceExtent);

        // 2. Canny Detect
        cannyDetect.run();

        // Type Detector
        sliceTypeDetector.setInputImageData(afterCannyImageData);
        vector<int> intersections;
        sliceTypeDetector.findHorizontalIntersectionPoints(intersections);
        cout << "num of intersection points: " << intersections.size() << endl;

        int numConnectedArea = intersections.size() / 2;
        vector<vector<int>> vecConnectedArea(numConnectedArea, vector<int>());
        // 如果相连区域较多，很可能是检测出了问题
        if (numConnectedArea <= 50) {
            for (int j = 0; j < numConnectedArea; j++) {
                sliceTypeDetector.findConnectedArea(intersections[j], vecConnectedArea[j]);
            }
        }

//        sliceTypeDetector.findConnectedArea(intersections[1], connectedArea0);
//        sliceTypeDetector.findConnectedArea(intersections[2], connectedArea1);
//
        vector<bool> vecIsCircle(numConnectedArea, false);

        // 如果相连区域较多，很可能是检测出了问题
        if (numConnectedArea <= 50) {
            for (int j = 0; j < numConnectedArea; j++) {
                vecIsCircle[j] = sliceTypeDetector.thisConnectedAreaIsCircle(vecConnectedArea[j]);

                cout << "area " << j << " is circle ? " << vecIsCircle[j] << endl;
            }
        }

        vector<vector<int> *> vecPCircles;

        // 如果相连区域较多，很可能是检测出了问题
        if (numConnectedArea <= 50) {
            for (int j = 0; j < numConnectedArea; j++) {
                if (vecIsCircle[j]) {
                    vecPCircles.push_back(&(vecConnectedArea[j]));
                }
            }
            cout << "Circle num is " << vecPCircles.size() << endl;

        }

        // Draw Circles
        drawCircles.setInputImageData(afterCannyImageData);
        drawCircles.setOutputImageData(afterDrawCircleImageData);
        vector<int> allCircle;
        for (auto pCircle : vecPCircles) {
            for (auto elem : *pCircle) {
                allCircle.push_back(elem);
            }
        }
        drawCircles.setCirclesToDraw(allCircle);
        drawCircles.run();


        multiply255.setInputImageData(afterDrawCircleImageData);
        multiply255.setOutputImageData(afterMultiply);
        multiply255.setOperatorToMultiplyK(255);
        multiply255.run();

        std::string _path;
        std::string _fileName;
        _path = "/Users/heliu/data/MultiTImeStep/OnlyCircle400/time1200/";
        _fileName = _path + std::to_string(i) + ".png";

        bool writeFile = true;
        if (writeFile) {
            writer->SetInputData(afterMultiply);
            writer->SetFileName(_fileName.c_str());
            writer->Write();
        }

//        neighborGrowing.outputImageClear();
        sliceTypeDetector.initializeParams();
    }

}



