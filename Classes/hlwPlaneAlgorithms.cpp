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

    if (planeSize[0] == -1 || planeSize[1] == -1) {
        computePlaneSize();
    }
    _coordinates[0] = _pointID / planeSize[0];
    _coordinates[1] = _pointID % planeSize[1];

}

int hlwPlaneAlgorithms::computeElementSize() {

    if(planeSize[0] == -1){
        computePlaneSize();
    }
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

void hlwPlaneAlgorithms::findAllIntersectionPoints(double *_p, int *_num) {

    int inputExtent[6];
    inputImageData->GetExtent(inputExtent);

    int horizontalLineExtent[6] = {0, 0, 0, 0, 0, 0};
    horizontalLineExtent[1] = inputExtent[1];
    horizontalLineExtent[2] = (inputExtent[3] - inputExtent[2]) / 2;
    horizontalLineExtent[3] = horizontalLineExtent[2];
    horizontalLineExtent[4] = inputExtent[4];
    horizontalLineExtent[5] = inputExtent[5];


    // 遇到的边界编号,从左往右应该遇到8次
    int edgeNum = 0;
    int edgeArray[8] = {0};
    auto pixel = (unsigned char *) (inputImageData->GetScalarPointerForExtent(horizontalLineExtent));
    for (int i = 0; i < horizontalLineExtent[1]; i++) {
        if (*pixel != 0) {
            edgeArray[edgeNum] = i;
            edgeNum++;
        }
        pixel++;
    }

    // Determine the position of the four points relative
    // to the center point to determine whether it is on
    // the left or right half.

    int _y = horizontalLineExtent[2];
    int _z = horizontalLineExtent[4];
    int ijk[3] = {0};
    ijk[1] = _y;
    ijk[2] = _z;
    vtkIdType pointIDs[8] = {0};
    for (int i = 0; i < edgeNum; i++) {
        ijk[0] = edgeArray[i];
        pointIDs[i] = inputImageData->ComputePointId(ijk);
    }

    for (int i = 0; i < edgeNum; i++) {
        _p[i] = pointIDs[i];
    }
    *_num = edgeNum;

}

void hlwPlaneAlgorithms::findCircle(int _pointId, vector<int> &_circlePoints) {
    queue<int> q;
    unordered_set<int> hasVisited;
    unordered_set<int> hasAddedToQueue;

    int coordinates[2];

    int eightNeighborsX[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int eightNeighborsY[] = {1, 1, 1, 0, 0, -1, -1, -1};

    q.push(_pointId);
    hasAddedToQueue.insert(_pointId);

    auto pixel = (unsigned char *) (inputImageData->GetScalarPointer());

    while (!q.empty()) {

        int qHead = q.front();

//        cout << "qHead " << qHead;
//        cout << "  queue size: " << q.size() << "  ";
//        cout << "  hash map size  " << hasVisited.size() << "  ";
//        cout << endl;

        q.pop();
        hasVisited.insert(qHead);
        computePlaneCoordinates(qHead, coordinates);
        for (int i = 0; i < 8; i++) {
            int newCoordinates[2];
            int newPid;

            newCoordinates[0] = coordinates[0] + eightNeighborsX[i];
            newCoordinates[1] = coordinates[1] + eightNeighborsY[i];
            newPid = computePlanePointID(newCoordinates);

            if (isInBound(newCoordinates[0], newCoordinates[1]) && pixel[newPid] == 1 &&
                hasVisited.find(newPid) == hasVisited.end() && hasAddedToQueue.find(newPid) == hasAddedToQueue.end()) {
                q.push(newPid);
                hasAddedToQueue.insert((newPid));
            }
        }

    }

    cout << "Point ID which value is 1" << endl;

    for (auto i = hasVisited.begin(); i != hasVisited.end(); i++) {
//        cout << *i << " ";
        _circlePoints.push_back(*i);
    }
}

