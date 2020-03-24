//
// Created by 何柳 on 2020/3/23.
//

#include "PlaneNeighborGrowing.h"
#include <queue>
#include <vector>

using std::vector;
using std::queue;
using std::sort;
using std::begin;
using std::end;

PlaneNeighborGrowing::PlaneNeighborGrowing(int neighborDistance) : neighborDistance(neighborDistance) {}

PlaneNeighborGrowing::PlaneNeighborGrowing() {
    neighborDistance = 2;
}

void PlaneNeighborGrowing::setNeighborDistance(int _neighborDistance) {
    PlaneNeighborGrowing::neighborDistance = _neighborDistance;
}

void PlaneNeighborGrowing::run() {
    auto inputScalarPointer = (unsigned char *) (inputImageData->GetScalarPointer());
    auto outputScalarPointer = (unsigned char *) (outputImageData->GetScalarPointer());

//    queue<int> notVisitedPointIDs;
    vector<int> notVisitedPointIDs;

    if (planeSize[0] == -1) {
        computePlaneSize();
    }


    for (int i = 0; i < elementSize; i++) {
        if (inputScalarPointer[i] == 1) {
            notVisitedPointIDs.push_back(i);
        }
    }

    // up , down, left, right
    int fourNeighborsX[] = {0, 0, -1, 1};
    int fourNeighborsY[] = {1, -1, 0, 0};

    int crossNeighborsD2X[] = {0, 0, 0, 0, -1, -2, 1, 2};
    int crossNeighborsD2Y[] = {1, 2, -1, -2, 0, 0, 0, 0};

    int crossNeighborsD3X[] = {0, 0, 0, 0, 0, 0, -1, -2, -3, 1, 2, 3};
    int crossNeighborsD3Y[] = {1, 2, 3, -1, -2, -3, 0, 0, 0, 0, 0, 0};

    int *neighborCoordinatesX = nullptr;
    int *neighborCoordinatesY = nullptr;

    int neighborArraySize = 0;

    switch (neighborDistance) {
        case 1:
            neighborCoordinatesX = fourNeighborsX;
            neighborCoordinatesY = fourNeighborsY;
            neighborArraySize = 4;
            break;
        case 2:
            neighborCoordinatesX = crossNeighborsD2X;
            neighborCoordinatesY = crossNeighborsD2Y;
            neighborArraySize = 8;
            break;
        case 3:
            neighborCoordinatesX = crossNeighborsD3X;
            neighborCoordinatesY = crossNeighborsD3Y;
            neighborArraySize = 12;
            break;
        default:
            cout << "error ! neighbor distance only support 1,2,3 " << endl;
            break;
    }

    for (int front : notVisitedPointIDs) {

        // 先给这个点标 1
        outputScalarPointer[front] = 1;

        int coors[2];
        computePlaneCoordinates(front, coors);

        int _x, _y;
        int _id;
        for (int j = 0; j < neighborArraySize; j++) {
            _x = coors[0] + neighborCoordinatesX[j];
            _y = coors[1] + neighborCoordinatesY[j];
            if (isInBound(_x, _y)) {
                _id = computePlanePointID(_x, _y);
                outputScalarPointer[_id] = 1;
            }
        }

    }
//    while (!notVisitedPointIDs.empty()) {
//    }
}

