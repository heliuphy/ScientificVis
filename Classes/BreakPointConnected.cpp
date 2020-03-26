//
// Created by 何柳 on 2020/3/26.
//

#include "BreakPointConnected.h"

void BreakPointConnected::findAllIntersectionPoints() {
    double p[8];
    int num;
    hlwPlaneAlgorithms::findAllIntersectionPoints(p, &num);
    allIntersectionPointIds.reserve(num);
    for (int i = 0; i < num; i++) {
        allIntersectionPointIds.push_back(p[i]);
    }
}

bool BreakPointConnected::isThisCircleClosed(int _pointId) {

    queue<int> q;
    unordered_set<int> hasAddedToQueue;

    int coordinates[2];

    int eightNeighborsX[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int eightNeighborsY[] = {1, 1, 1, 0, 0, -1, -1, -1};

    q.push(_pointId);
    hasAddedToQueue.insert(_pointId);

    auto pixel = (unsigned char *) (inputImageData->GetScalarPointer());

    while (!q.empty()) {

        int qHead = q.front();

        q.pop();
        computePlaneCoordinates(qHead, coordinates);
        for (int i = 0; i < 8; i++) {
            int newCoordinates[2];
            int newPid;

            newCoordinates[0] = coordinates[0] + eightNeighborsX[i];
            newCoordinates[1] = coordinates[1] + eightNeighborsY[i];
            newPid = computePlanePointID(newCoordinates);

            if (isInBound(newCoordinates[0], newCoordinates[1]) && pixel[newPid] == 1 &&
                hasAddedToQueue.find(newPid) == hasAddedToQueue.end()) {
                q.push(newPid);
                hasAddedToQueue.insert((newPid));
            }
        }

    }

    cout << "Point ID which value is 1" << endl;

//    for (auto i = hasVisited.begin(); i != hasVisited.end(); i++) {
////        cout << *i << " ";
//        _circlePoints.push_back(*i);
//    }
//    return false;
}
