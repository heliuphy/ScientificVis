//
// Created by 何柳 on 2020/3/26.
//

#include "AreaDelete.h"

#include <utility>

void AreaDelete::deleteArea() {
    auto inputPixel = (unsigned char *) (inputImageData->GetScalarPointer());
    auto outputPixel = (unsigned char *) (outputImageData->GetScalarPointer());

    if (elementSize == -1) {
        computeElementSize();
    }
    assert(elementSize >= 0);
    memcpy(outputPixel, inputPixel, elementSize * sizeof(unsigned char));

    for (auto i :areaVector) {
        outputPixel[i] = 0;
    }
}

void AreaDelete::run() {
    deleteArea();
}

void AreaDelete::addToDeleteArea(int _pointID) {
    vector<int> thisConnectedArea;
    findConnectedArea(_pointID, thisConnectedArea);

    for (auto i : thisConnectedArea) {
        areaVector.push_back(i);
    }

    numOfAreaToDelete++;
}

int AreaDelete::getNumOfAreaToDelete() {
    return numOfAreaToDelete;
}

