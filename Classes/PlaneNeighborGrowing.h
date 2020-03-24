//
// Created by 何柳 on 2020/3/23.
//

#ifndef MYPROJ_PLANENEIGHBORGROWING_H
#define MYPROJ_PLANENEIGHBORGROWING_H

#include "hlwPlaneAlgorithms.h"
#include <vtkImageData.h>

// 实现邻域生长算法
class PlaneNeighborGrowing: public hlwPlaneAlgorithms {

public:
    PlaneNeighborGrowing();

    PlaneNeighborGrowing(int neighborDistance);

    void run() override;

    void setNeighborDistance(int _neighborDistance);


protected:
    int neighborDistance;
};


#endif //MYPROJ_PLANENEIGHBORGROWING_H
