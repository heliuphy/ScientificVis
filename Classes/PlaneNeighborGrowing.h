//
// Created by 何柳 on 2020/3/23.
//

#ifndef MYPROJ_PLANENEIGHBORGROWING_H
#define MYPROJ_PLANENEIGHBORGROWING_H

#define GROW_ON_ALL_IMAGE 0
#define GROW_ON_CIRCLE 1

#include "hlwPlaneAlgorithms.h"
#include <vtkImageData.h>
#include <vector>
#include <queue>
#include <unordered_set>

using std::vector;
using std::queue;
using std::unordered_set;

// 实现邻域生长算法
class PlaneNeighborGrowing : public hlwPlaneAlgorithms {

public:
    PlaneNeighborGrowing();

    void run() override;

    void setNeighborDistance(int _neighborDistance);

    void setMode(int _m);

    void setCirclePointsVector(vector<int> *_circlePointsVector);

    void outputImageClear();

protected:
    void neighborGrowOnSpecifiedCircle();

    void neighborGrowOnAllImage();

protected:
    int neighborDistance;
    int growMode;
    bool isInputCopyToOutput;
    vector<int> *circlePoints;

};


#endif //MYPROJ_PLANENEIGHBORGROWING_H
