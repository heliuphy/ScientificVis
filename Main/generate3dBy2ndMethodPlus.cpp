//
// Created by 何柳 on 2020/3/24.
//

#include "generate3dByFIrstMethod.h"
#include "CircleDelete.h"
#include "SliceTypeDetector.h"
#include <vtkMetaImageWriter.h>

int main() {

    //==========================================================================================
    //                        ==========       READ FILE        ==========
    //==========================================================================================
    // Reading 3d data plane and reference plane
    // /Users/heliu/OneDrive/Data/node-centered
    vtkSmartPointer<vtkMetaImageReader> d3reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    d3reader->SetFileName("/Users/heliu/OneDrive/Data/node-centered/Step-1-Reslice/volume800Meta.mhd");
    d3reader->Update();

    vtkSmartPointer<vtkMetaImageReader> referencePlaneReader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    referencePlaneReader->SetFileName("/Users/heliu/OneDrive/Data/node-centered/Step-1-Reslice/output/plane.mhd");
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


    vtkSmartPointer<vtkImageData> afterCircleDeleteImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterCircleDeleteImageData->SetOrigin(referenceInfo.Origin);
    afterCircleDeleteImageData->SetSpacing(referenceInfo.Spacing);
    afterCircleDeleteImageData->SetExtent(referenceInfo.Extent);
    afterCircleDeleteImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);


    vtkSmartPointer<vtkImageData> afterMultiply =
            vtkSmartPointer<vtkImageData>::New();
    afterMultiply->SetOrigin(referenceInfo.Origin);
    afterMultiply->SetSpacing(referenceInfo.Spacing);
    afterMultiply->SetExtent(referenceInfo.Extent);
    afterMultiply->AllocateScalars(VTK_UNSIGNED_CHAR, 1);


    vtkSmartPointer<vtkMetaImageWriter> writer =
            vtkSmartPointer<vtkMetaImageWriter>::New();

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

    CircleDelete circleDelete;

    PlaneNeighborGrowing neighborGrowing;
    neighborGrowing.setNeighborDistance(3);

    hlwImageMath multiply255;

    //==========================================================================================
    //                        ==========       RUN        ==========
    //==========================================================================================
    vector<int> errorList;

    for (int i = 0; i < 400; i++) {

        cout << "Now doing " << i << "th Plane! " << endl;
        // 1. 切面
        imageSlice.setSliceIndex(i);
        imageSlice.computeSlicePlaneInformation();
        imageSlice.run();

        int thisSliceExtent[6];
        imageSlice.getSliceExtent(thisSliceExtent);

        // 2. Canny Detect
        cannyDetect.run();

        // 3. Determine whether the boundary type is 6688 or 8888
        sliceTypeDetector.setInputImageData(afterCannyImageData);
        sliceTypeDetector.detectType();
        int type = 0;
        type = sliceTypeDetector.getType();
        cout << "This slice's type is " << type << endl;

        circleDelete.setInputImageData(afterCannyImageData);

        bool writeFile = true;

        if (type == 6688) {

            vector<int> fakeInnerCircle;
            vector<int> fakeOuterCircle;

            vector<vector<int>> InnerCircle = {{},
                                               {},
                                               {},
                                               {}};

            sliceTypeDetector.findConnectedArea(sliceTypeDetector.getBackslashIntersections().at(3),
                                                InnerCircle[0]);
            sliceTypeDetector.findConnectedArea(sliceTypeDetector.getBackslashIntersections().at(4),
                                                InnerCircle[2]);
            sliceTypeDetector.findConnectedArea(sliceTypeDetector.getSlashIntersections().at(3),
                                                InnerCircle[1]);
            sliceTypeDetector.findConnectedArea(sliceTypeDetector.getSlashIntersections().at(4),
                                                InnerCircle[3]);

            for (const auto &v : InnerCircle) {
                for (auto p : v) {
                    fakeInnerCircle.push_back(p);
                }
            }

            sliceTypeDetector.findCircleOld(sliceTypeDetector.getHorizontalIntersections().at(1),
                                            fakeOuterCircle);

            for (auto p : fakeOuterCircle) {
                fakeInnerCircle.push_back(p);
            }


            // Delete fake inner circle and fake outer circle
            circleDelete.setInputImageData(afterCannyImageData);
            circleDelete.setOutputImageData(afterCircleDeleteImageData);
            circleDelete.setDeleteCircle(fakeInnerCircle);
            circleDelete.run();

        } else if (type == 8888) {

            if (i == 145 || i == 254) {

                vector<int> fakeOuterCircle;
                vector<int> fakeInnerCircle;

                vector<vector<int>> OuterCircle = {{},
                                                   {},
                                                   {},
                                                   {},
                                                   {},
                                                   {},
                                                   {},
                                                   {}};

                sliceTypeDetector.findConnectedArea(sliceTypeDetector.getBackslashIntersections().at(1),
                                                    OuterCircle[0]);
                sliceTypeDetector.findConnectedArea(sliceTypeDetector.getBackslashIntersections().at(6),
                                                    OuterCircle[4]);
                sliceTypeDetector.findConnectedArea(sliceTypeDetector.getHorizontalIntersections().at(1),
                                                    OuterCircle[1]);
                sliceTypeDetector.findConnectedArea(sliceTypeDetector.getHorizontalIntersections().at(6),
                                                    OuterCircle[5]);
                sliceTypeDetector.findConnectedArea(sliceTypeDetector.getSlashIntersections().at(1),
                                                    OuterCircle[2]);
                sliceTypeDetector.findConnectedArea(sliceTypeDetector.getSlashIntersections().at(6),
                                                    OuterCircle[6]);
                sliceTypeDetector.findConnectedArea(sliceTypeDetector.getVerticalIntersections().at(1),
                                                    OuterCircle[3]);
                sliceTypeDetector.findConnectedArea(sliceTypeDetector.getVerticalIntersections().at(6),
                                                    OuterCircle[7]);

                for (const auto &v : OuterCircle) {
                    for (auto p : v) {
                        fakeOuterCircle.push_back(p);
                    }
                }

                sliceTypeDetector.findCircleOld(sliceTypeDetector.getHorizontalIntersections().at(3),
                                                fakeInnerCircle);

                for (auto p :fakeInnerCircle) {
                    fakeOuterCircle.push_back(p);
                }


                // Delete fake inner circle and fake outer circle
                circleDelete.setInputImageData(afterCannyImageData);
                circleDelete.setOutputImageData(afterCircleDeleteImageData);
                circleDelete.setDeleteCircle(fakeOuterCircle);
                circleDelete.run();

            } else if (i == 143 || i == 255) {

                vector<int> OuterCircle;
                vector<vector<int>> InnerCircles = {{},
                                                    {},
                                                    {},
                                                    {},
                                                    {},
                                                    {},
                                                    {},
                                                    {}};


                sliceTypeDetector.findConnectedArea(sliceTypeDetector.getHorizontalIntersections().at(3),
                                                    InnerCircles[0]);
                sliceTypeDetector.findConnectedArea(sliceTypeDetector.getHorizontalIntersections().at(4),
                                                    InnerCircles[1]);
                sliceTypeDetector.findConnectedArea(sliceTypeDetector.getVerticalIntersections().at(3),
                                                    InnerCircles[2]);
                sliceTypeDetector.findConnectedArea(sliceTypeDetector.getVerticalIntersections().at(4),
                                                    InnerCircles[3]);
                sliceTypeDetector.findConnectedArea(sliceTypeDetector.getSlashIntersections().at(3),
                                                    InnerCircles[4]);
                sliceTypeDetector.findConnectedArea(sliceTypeDetector.getSlashIntersections().at(4),
                                                    InnerCircles[5]);
                sliceTypeDetector.findConnectedArea(sliceTypeDetector.getBackslashIntersections().at(3),
                                                    InnerCircles[6]);
                sliceTypeDetector.findConnectedArea(sliceTypeDetector.getBackslashIntersections().at(4),
                                                    InnerCircles[7]);

                sliceTypeDetector.findConnectedArea(sliceTypeDetector.getHorizontalIntersections().at(1),
                                                    OuterCircle);

                for (const auto &v : InnerCircles) {
                    for (auto p : v) {
                        OuterCircle.push_back(p);
                    }
                }

                // Delete fake inner circle and fake outer circle
                circleDelete.setInputImageData(afterCannyImageData);
                circleDelete.setOutputImageData(afterCircleDeleteImageData);
                circleDelete.setDeleteCircle(OuterCircle);
                circleDelete.run();


            } else {

                vector<int> InnerCircle;
                vector<int> OuterCircle;

                sliceTypeDetector.findCircleOld(sliceTypeDetector.getHorizontalIntersections().at(1),
                                                OuterCircle);
                sliceTypeDetector.findCircleOld((sliceTypeDetector.getHorizontalIntersections().at(3)),
                                                InnerCircle);
                for (auto p : OuterCircle) {
                    InnerCircle.push_back(p);
                }

                circleDelete.setInputImageData(afterCannyImageData);
                circleDelete.setOutputImageData(afterCircleDeleteImageData);
                circleDelete.setDeleteCircle(InnerCircle);
                circleDelete.run();

            }
        } else if (type == 4444) {

            vector<int> OuterCircle;

            sliceTypeDetector.findCircleOld(sliceTypeDetector.getHorizontalIntersections().at(1),
                                            OuterCircle);

            circleDelete.setInputImageData(afterCannyImageData);
            circleDelete.setOutputImageData(afterCircleDeleteImageData);
            circleDelete.setDeleteCircle(OuterCircle);
            circleDelete.run();
        } else if (type == 6666) {

            vector<int> OuterCircle;

            sliceTypeDetector.findCircleOld(sliceTypeDetector.getHorizontalIntersections().at(1),
                                            OuterCircle);

            circleDelete.setInputImageData(afterCannyImageData);
            circleDelete.setOutputImageData(afterCircleDeleteImageData);
            circleDelete.setDeleteCircle(OuterCircle);
            circleDelete.run();
        } else if (type == 2244) {

            vector<int> OuterCircle;

            circleDelete.setInputImageData(afterCannyImageData);
            circleDelete.setOutputImageData(afterCircleDeleteImageData);
            circleDelete.setDeleteCircle(OuterCircle);
            circleDelete.run();
        } else if (type == 8800) {
            vector<int> InnerCircle;
            vector<vector<int>> InnerCircles = {{},
                                                {},
                                                {},
                                                {},
                                                {},
                                                {},
                                                {},
                                                {}
            };

            vector<int> OuterCircle;
            vector<vector<int>> FourSmallLine = {{},
                                                 {},
                                                 {},
                                                 {}};

            sliceTypeDetector.findCircleOld(sliceTypeDetector.getHorizontalIntersections().at(1),
                                            OuterCircle);

            sliceTypeDetector.findCircleOld(sliceTypeDetector.getSlashIntersections().at(4),
                                            FourSmallLine[0]);
            sliceTypeDetector.findCircleOld(sliceTypeDetector.getSlashIntersections().at(5),
                                            FourSmallLine[1]);
            sliceTypeDetector.findCircleOld(sliceTypeDetector.getBackslashIntersections().at(4),
                                            FourSmallLine[2]);
            sliceTypeDetector.findCircleOld(sliceTypeDetector.getBackslashIntersections().at(5),
                                            FourSmallLine[3]);

            sliceTypeDetector.findCircleOld(sliceTypeDetector.getHorizontalIntersections().at(3),
                                            InnerCircles[0]);
            sliceTypeDetector.findCircleOld(sliceTypeDetector.getHorizontalIntersections().at(6),
                                            InnerCircles[1]);
            sliceTypeDetector.findCircleOld(sliceTypeDetector.getVerticalIntersections().at(3),
                                            InnerCircles[2]);
            sliceTypeDetector.findCircleOld(sliceTypeDetector.getVerticalIntersections().at(6),
                                            InnerCircles[3]);
            sliceTypeDetector.findCircleOld(sliceTypeDetector.getSlashIntersections().at(3),
                                            InnerCircles[4]);
            sliceTypeDetector.findCircleOld(sliceTypeDetector.getSlashIntersections().at(6),
                                            InnerCircles[5]);
            sliceTypeDetector.findCircleOld(sliceTypeDetector.getBackslashIntersections().at(3),
                                            InnerCircles[6]);
            sliceTypeDetector.findCircleOld(sliceTypeDetector.getBackslashIntersections().at(6),
                                            InnerCircles[7]);

            for (const auto &v : InnerCircles) {
                for (auto p : v) {
                    InnerCircle.push_back(p);
                }
            }

            for (const auto &v:FourSmallLine) {
                for (auto p : v) {
                    InnerCircle.push_back(p);
                }
            }

            for (auto p : OuterCircle) {
                InnerCircle.push_back(p);
            }

            circleDelete.setInputImageData(afterCannyImageData);
            circleDelete.setOutputImageData(afterCircleDeleteImageData);
            circleDelete.setDeleteCircle(InnerCircle);
            circleDelete.run();

        } else {  // type == -1
//            writeFile = false;
//            errorList.push_back(i);

            vector<int> InnerCircle;
            vector<int> OuterCircle;

            sliceTypeDetector.findCircleOld(sliceTypeDetector.getHorizontalIntersections().at(1),
                                            OuterCircle);
            sliceTypeDetector.findCircleOld((sliceTypeDetector.getHorizontalIntersections().at(3)),
                                            InnerCircle);

            for (auto p : OuterCircle) {
                InnerCircle.push_back(p);
            }

            circleDelete.setInputImageData(afterCannyImageData);
            circleDelete.setOutputImageData(afterCircleDeleteImageData);
            circleDelete.setDeleteCircle(InnerCircle);
            circleDelete.run();

        }

        neighborGrowing.setInputImageData(afterCircleDeleteImageData);
        neighborGrowing.setOutputImageData(afterNeighborGrowImageData);
        neighborGrowing.setMode(GROW_ON_ALL_IMAGE);
        neighborGrowing.run();


        auto planePointerOf3dOutputData = (unsigned char *) (outputImageData->GetScalarPointerForExtent(
                thisSliceExtent));

        auto afterNeighborGrowPointer = (unsigned char *) (afterNeighborGrowImageData->GetScalarPointer());

        int dims[3];
        afterNeighborGrowImageData->GetDimensions(dims);

        int n = dims[0] * dims[1] * dims[2];

        memcpy(planePointerOf3dOutputData, afterNeighborGrowPointer, n * sizeof(unsigned char));

        neighborGrowing.outputImageClear();
        sliceTypeDetector.initializeParams();
    }

    std::string _fileName;
    _fileName = "/Users/heliu/OneDrive/Data/node-centered/step7-3d/2ndMethodPlus/dim3.mhd";

    writer->SetInputData(outputImageData);
    writer->SetFileName(_fileName.c_str());
    writer->Write();

}



