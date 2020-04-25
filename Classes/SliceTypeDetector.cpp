//
// Created by 何柳 on 2020/4/22.
//

#include "SliceTypeDetector.h"

SliceTypeDetector::SliceTypeDetector() {

}

SliceTypeDetector::~SliceTypeDetector() {

}

void SliceTypeDetector::findHorizontalIntersectionPoints(vector<int> &pointArray) {

    int inputExtent[6];
    inputImageData->GetExtent(inputExtent);

    //DEBUG
//    cout << "inputExtent: ";
//    for (int i = 0; i < 6; i++) {
//        cout << inputExtent[i] << " ";
//    }
//    cout << endl;
    //

    int horizontalLineExtent[6] = {0, 0, 0, 0, 0, 0};
    horizontalLineExtent[1] = inputExtent[1];
    horizontalLineExtent[2] = (inputExtent[3] - inputExtent[2]) / 2;
    horizontalLineExtent[3] = horizontalLineExtent[2];
    horizontalLineExtent[4] = inputExtent[4];
    horizontalLineExtent[5] = inputExtent[5];

    //DEBUG
//    cout << "horizontalLineExtent: ";
//    for (int i = 0; i < 6; i++) {
//        cout << horizontalLineExtent[i] << " ";
//    }
//    cout << endl;
    //

    vector<int> edgeArray;
    auto pixel = (unsigned char *) (inputImageData->GetScalarPointerForExtent(horizontalLineExtent));
    for (int i = 0; i <= horizontalLineExtent[1]; i++) {
        if (*pixel != 0) {
            edgeArray.push_back(i);
        }
        pixel++;
    }

    int _y = horizontalLineExtent[2];
    int _z = horizontalLineExtent[4];
    int ijk[3] = {0};
    ijk[1] = _y;
    ijk[2] = _z;

    int edgeNum = edgeArray.size();

    for (int i = 0; i < edgeNum; i++) {
        ijk[0] = edgeArray[i];
        pointArray.push_back(inputImageData->ComputePointId(ijk));
    }

}

void SliceTypeDetector::findVerticalIntersectionPoints(vector<int> &pointArray) {

    int inputExtent[6];
    inputImageData->GetExtent(inputExtent);

    int verticalLineExtent[6] = {0, 0, 0, 0, 0, 0};
    verticalLineExtent[0] = (inputExtent[1] - inputExtent[0]) / 2;
    verticalLineExtent[1] = verticalLineExtent[0];
    verticalLineExtent[2] = inputExtent[2];
    verticalLineExtent[3] = inputExtent[3];
    verticalLineExtent[4] = inputExtent[4];
    verticalLineExtent[5] = inputExtent[5];

    //DEBUG
    cout << "verticalExtent: ";
    for (int i = 0; i < 6; i++) {
        cout << verticalLineExtent[i] << " ";
    }
    cout << endl;
    //

    vector<int> edgeArray;

    int _x = verticalLineExtent[0];
    int _z = verticalLineExtent[4];
    int ijk[3] = {0};
    ijk[0] = _x;
    ijk[2] = _z;

//    auto pixel = (unsigned char *) (inputImageData->GetScalarPointerForExtent(verticalLineExtent));
    for (int i = 0; i <= verticalLineExtent[3]; i++) {
        ijk[1] = i;
        auto pixel = (unsigned char *) (inputImageData->GetScalarPointer(ijk[0], ijk[1], ijk[2]));
        if (*pixel != 0) {
            edgeArray.push_back(i);
        }
    }


    int edgeNum = edgeArray.size();

    for (int i = 0; i < edgeNum; i++) {
        ijk[1] = edgeArray[i];
        pointArray.push_back(inputImageData->ComputePointId(ijk));
    }

}

void SliceTypeDetector::findSlashIntersectionPoints(vector<int> &pointArray) {

    int inputExtent[6];
    inputImageData->GetExtent(inputExtent);

    int xMin = inputExtent[0];
    int xMax = inputExtent[1];
    int yMin = inputExtent[2];
    int yMax = inputExtent[3];

    int i = xMin, j = yMin, k = inputExtent[4];
    while (i <= xMax && j <= yMax) {
        auto pixel = (unsigned char *) (inputImageData->GetScalarPointer(i, j, k));
        if (*pixel != 0) {
            int ijk[3] = {0};
            ijk[0] = i;
            ijk[1] = j;
            ijk[2] = k;
            pointArray.push_back(inputImageData->ComputePointId(ijk));
        }
        i++;
        j++;
    }

}

void SliceTypeDetector::findBackslashIntersectionPoints(vector<int> &pointArray) {

    int inputExtent[6];
    inputImageData->GetExtent(inputExtent);

    int xMin = inputExtent[0];
    int xMax = inputExtent[1];
    int yMin = inputExtent[2];
    int yMax = inputExtent[3];

    int i = xMin, j = yMax, k = inputExtent[4];
    while (i <= xMax && j >= yMin) {
        auto pixel = (unsigned char *) (inputImageData->GetScalarPointer(i, j, k));
        if (*pixel != 0) {
            int ijk[3] = {0};
            ijk[0] = i;
            ijk[1] = j;
            ijk[2] = k;
            pointArray.push_back(inputImageData->ComputePointId(ijk));
        }
        i++;
        j--;
    }
}

void SliceTypeDetector::run() {

}

void SliceTypeDetector::detectType() {
    int horizontalIntersectionNum = 0;
    int verticalIntersectionNum = 0;
    int slashIntersectionNum = 0;
    int backslashIntersectionNum = 0;

    findHorizontalIntersectionPoints();
    findVerticalIntersectionPoints();
    findSlashIntersectionPoints();
    findBackslashIntersectionPoints();

    horizontalIntersectionNum = horizontalIntersections.size();
    verticalIntersectionNum = verticalIntersections.size();
    slashIntersectionNum = slashIntersections.size();
    backslashIntersectionNum = backslashIntersections.size();

    if (horizontalIntersectionNum == 8 &&
        verticalIntersectionNum == 8 &&
        slashIntersectionNum == 8 &&
        backslashIntersectionNum == 8
            ) {
        type = 8888;
    } else if (horizontalIntersectionNum == 6 &&
               verticalIntersectionNum == 6 &&
               slashIntersectionNum == 8 &&
               backslashIntersectionNum == 8) {
        type = 6688;
    } else if (horizontalIntersectionNum == 4 &&
               verticalIntersectionNum == 4 &&
               slashIntersectionNum == 4 &&
               backslashIntersectionNum == 4) {
        type = 4444;
    } else if (horizontalIntersectionNum == 6 &&
               verticalIntersectionNum == 6 &&
               slashIntersectionNum == 6 &&
               backslashIntersectionNum == 6) {
        type = 6666;
    } else if (horizontalIntersectionNum == 2 &&
               verticalIntersectionNum == 2 &&
               slashIntersectionNum == 4 &&
               backslashIntersectionNum == 4) {
        type = 2244;
    } else {
        type = -1;
    }
}

void SliceTypeDetector::findHorizontalIntersectionPoints() {
    findHorizontalIntersectionPoints(horizontalIntersections);
}

void SliceTypeDetector::findVerticalIntersectionPoints() {
    findVerticalIntersectionPoints(verticalIntersections);
}

void SliceTypeDetector::findSlashIntersectionPoints() {
    findSlashIntersectionPoints(slashIntersections);
}

void SliceTypeDetector::findBackslashIntersectionPoints() {
    findBackslashIntersectionPoints(backslashIntersections);
}

int SliceTypeDetector::getType() const {
    return type;
}

const vector<int> &SliceTypeDetector::getHorizontalIntersections() const {
    return horizontalIntersections;
}

const vector<int> &SliceTypeDetector::getVerticalIntersections() const {
    return verticalIntersections;
}

const vector<int> &SliceTypeDetector::getSlashIntersections() const {
    return slashIntersections;
}

const vector<int> &SliceTypeDetector::getBackslashIntersections() const {
    return backslashIntersections;
}

void SliceTypeDetector::outputImageClear() {
    if (elementSize == -1) {
        computeElementSize();
    }
    auto outputPointer = (unsigned char *) (outputImageData->GetScalarPointer());

    memset(outputPointer, 0, elementSize * sizeof(unsigned char));
}

void SliceTypeDetector::initializeParams() {
    type = 0;
    horizontalIntersections.clear();
    verticalIntersections.clear();
    slashIntersections.clear();
    backslashIntersections.clear();
}
