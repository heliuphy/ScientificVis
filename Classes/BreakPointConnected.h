//
// Created by 何柳 on 2020/3/26.
//

#ifndef MYPROJ_BREAKPOINTCONNECTED_H
#define MYPROJ_BREAKPOINTCONNECTED_H


#include <vector>
#include <queue>
#include <unordered_set>
#include "hlwPlaneAlgorithms.h"

using std::vector;
using std::queue;
using std::unordered_set;

class BreakPointConnected : public hlwPlaneAlgorithms {

public:
    void findAllIntersectionPoints();

    bool isThisCircleClosed(int _pointId);

protected:
    vector<int> allIntersectionPointIds;

};


#endif //MYPROJ_BREAKPOINTCONNECTED_H
