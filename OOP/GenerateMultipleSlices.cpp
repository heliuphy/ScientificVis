//
// Created by 何柳 on 2020/3/23.
//
#include "AlgoBase.h"
#include "GenerateMultipleSlices.h"
#include <fstream>
#include <iostream>

struct ImageOriginSpacingExtent {
    double Origin[3];
    double Spacing[3];
    int Extent[6];
};

GenerateMultipleSlices::GenerateMultipleSlices(int zStart, int zEnd, int planeSpacing, vtkImageData *input2DImageData,
                                               vtkImageData *input3DImageData) : AlgoBase(zStart, zEnd, planeSpacing,
                                                                                          input2DImageData,
                                                                                          input3DImageData) {}

void GenerateMultipleSlices::getZeroOneNumOfSpecificPlane(vector<int> &_positions) {

//    fstream file;
//    file.open("/Users/heliu/temp/node-centered/step5-SpecialCase/out.txt", ios::app);
    for (auto i:_positions) {

        generateOneSliceSaveToTempFloat2d(i);
        doCanny();
        doImageFillAuto();

        int count0 = 0, count1 = 0;
        auto afterFillPointer = (unsigned char *) (afterFillImageData->GetScalarPointer());
        int _dims[3];
        afterFillImageData->GetDimensions(_dims);
        std::sort(std::begin(_dims), std::end(_dims));
        assert(_dims[0] == 1);
        int _n = _dims[1] * _dims[2];
        for (int j = 0; j < _n; j++) {
            if (afterFillPointer[j] == 0) {
                count0++;
            } else {
                count1++;
            }
        }
//        cout << "i = " << i << "count0 = " << count0 << "  count1 = " << count1 << endl;
//        file << "i = " << i << "  count0 = " << count0 << "  count1 = " << count1 << endl;
    }
//    file.close();
}

void GenerateMultipleSlices::getZeroOneNumOfSpecificPlane(vector<int> &_positions, vector<int> &_count1s) {
    for (auto i:_positions) {

        generateOneSliceSaveToTempFloat2d(i);
        doCanny();
        doImageFillAuto();

        int count0 = 0, count1 = 0;
        auto afterFillPointer = (unsigned char *) (afterFillImageData->GetScalarPointer());
        int _dims[3];
        afterFillImageData->GetDimensions(_dims);
        std::sort(std::begin(_dims), std::end(_dims));
        assert(_dims[0] == 1);
        int _n = _dims[1] * _dims[2];
        for (int j = 0; j < _n; j++) {
            if (afterFillPointer[j] == 0) {
                count0++;
            } else {
                count1++;
            }
        }
        _count1s.push_back(count1);
    }
}

void
GenerateMultipleSlices::findIndexOfSpecialPlanes(vector<int> &_indexes, vector<int> &_count1s, const bool _useCache) {

    if (_useCache) {
        _indexes.push_back(1);
        _indexes.push_back(2);
        _indexes.push_back(9);
        _indexes.push_back(10);
        _indexes.push_back(389);
        _indexes.push_back(390);
        _indexes.push_back(397);
        _indexes.push_back(399);
    } else {
        for (int i = 0; i < zIndexes.size(); i++) {
            if (_count1s[i] >= 1e5) {
                cout << "  " << i;
            }
        }

    }
}

int main() {

    vtkSmartPointer<vtkMetaImageReader> d3reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    d3reader->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/volume800Meta.mhd");
    d3reader->Update();

    vtkSmartPointer<vtkMetaImageReader> planeReader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    planeReader->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/output/plane.mhd");
    planeReader->Update();

    vtkSmartPointer<vtkImageData> input3DImageData = d3reader->GetOutput();
    vtkSmartPointer<vtkImageData> planeImageData = planeReader->GetOutput();

    int zStart = 0;
    int zEnd = 399;
    int planeSpacing = 1;

    GenerateMultipleSlices generateMultipleSlices(zStart,
                                                  zEnd,
                                                  planeSpacing,
                                                  planeImageData,
                                                  input3DImageData);


    vtkSmartPointer<vtkImageData> tempPlaneImageData =
            vtkSmartPointer<vtkImageData>::New();
    generateMultipleSlices.setTempFloat2DImage(tempPlaneImageData);
//    generateMultipleSlices.generateOneSliceSaveToTempFloat2d(10);

    generateMultipleSlices.setToCannyImageData(tempPlaneImageData);

    vtkSmartPointer<vtkImageData> afterCannyImageData =
            vtkSmartPointer<vtkImageData>::New();
    generateMultipleSlices.setAfterCannyImageData(afterCannyImageData);

//    generateMultipleSlices.doCanny();

    vtkSmartPointer<vtkImageData> afterFillImageData
            = vtkSmartPointer<vtkImageData>::New();
    generateMultipleSlices.setAfterFillImageData(afterFillImageData);
//    generateMultipleSlices.doImageFillAuto();

    vtkSmartPointer<vtkImageData> afterSubImageData =
            vtkSmartPointer<vtkImageData>::New();
    generateMultipleSlices.setAfterSubImageData(afterSubImageData);
//    generateMultipleSlices.twoImagesSub(afterFillImageData, afterCannyImageData, afterSubImageData);

    vtkSmartPointer<vtkImageData> multiply =
            vtkSmartPointer<vtkImageData>::New();
    generateMultipleSlices.setMultiply255(multiply);
//    generateMultipleSlices.booleanImageMultiplyByK(afterSubImageData, multiply, 255);

    vector<int> pos;
    for (int i = 0; i < 400; i++) {
        pos.push_back(i);
    }
    vector<int> count1s;
    generateMultipleSlices.getZeroOneNumOfSpecificPlane(pos, count1s);

    vector<int> specialIndexes;
    generateMultipleSlices.findIndexOfSpecialPlanes(specialIndexes, count1s, true);


    vtkSmartPointer<vtkPNGWriter> writer =
            vtkSmartPointer<vtkPNGWriter>::New();
    writer->SetInputData(multiply);
    writer->SetFileName("/Users/heliu/temp/node-centered/step5-SpecialCase/10.png");
    writer->Write();


}
