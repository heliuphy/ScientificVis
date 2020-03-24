//
// Created by 何柳 on 2020/3/23.
//

#include "hlwPlaneAlgorithms.h"
#include <queue>

using std::sort;
using std::begin;
using std::end;
using std::queue;

hlwPlaneAlgorithms::hlwPlaneAlgorithms() {
    planeSize = new int[2];
    planeSize[0] = -1;
    planeSize[1] = -1;

    planeCoordinates = new int[2];
    planeCoordinates[0] = -1;
    planeCoordinates[1] = -1;

    elementSize = -1;
}

hlwPlaneAlgorithms::~hlwPlaneAlgorithms() {
    delete[] planeSize;
    delete[] planeCoordinates;
}

void hlwPlaneAlgorithms::computePlaneSize() {

    auto inputScalarPointer = (unsigned char *) (inputImageData->GetScalarPointer());
    auto outputScalarPointer = (unsigned char *) (outputImageData->GetScalarPointer());

    int _dims[3];
    inputImageData->GetDimensions(_dims);

    // delete element which value is 1
    int valueOneIndex = 0;
    for (int i = 0; i < 3; i++) {
        if (_dims[i] == 1) {
            valueOneIndex = i;
            break;
        }
    }

    switch (valueOneIndex) {
        case 0:
            planeSize[0] = _dims[1];
            planeSize[1] = _dims[2];
            break;
        case 1:
            planeSize[0] = _dims[0];
            planeSize[1] = _dims[2];
            break;
        case 2:
            planeSize[0] = _dims[0];
            planeSize[1] = _dims[1];
            break;

    }

    elementSize = planeSize[0] * planeSize[1];

}

void hlwPlaneAlgorithms::computePlaneCoordinates(int _pointID, int *_coordinates) {

    _coordinates[0] = _pointID / planeSize[0];
    _coordinates[1] = _pointID % planeSize[1];

}

int hlwPlaneAlgorithms::computeElementSize() {

    assert(planeSize[0] != -1);
    elementSize = planeSize[0] * planeSize[1];

    return elementSize;
}

bool hlwPlaneAlgorithms::isInBound(int _pos0, int _pos1) {

    if (_pos0 < 0 || _pos0 >= planeSize[0]) {
        return false;
    }
    return !(_pos1 < 0 || _pos1 >= planeSize[1]);
}

int hlwPlaneAlgorithms::computePlanePointID(int *_coordinates) {

    assert(_coordinates[0] >= 0);
    return _coordinates[0] * planeSize[0] + _coordinates[1];
}

int hlwPlaneAlgorithms::computePlanePointID(int _coordinates0, int _coordinates1) {

    assert(_coordinates0 >= 0);
    return _coordinates0 * planeSize[0] + _coordinates1;
}
