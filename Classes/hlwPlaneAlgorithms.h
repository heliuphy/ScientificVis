//
// Created by 何柳 on 2020/3/23.
//

#ifndef MYPROJ_HLWPLANEALGORITHMS_H
#define MYPROJ_HLWPLANEALGORITHMS_H

#include "hlwAlgorithms.h"

class hlwPlaneAlgorithms : public hlwAlgorithms{
public:
    hlwPlaneAlgorithms();

    ~hlwPlaneAlgorithms();

    void computePlaneSize();

    void computePlaneCoordinates(int _pointID, int *_coordinates);

    int computePlanePointID(int *_coordinates);

    int computeElementSize();

    bool isInBound(int _pos0, int _pos1);
protected:

    int *planeSize;
    int elementSize;
    int *planeCoordinates;

    int computePlanePointID(int _coordinates0, int _coordinates1);
};



#endif //MYPROJ_HLWPLANEALGORITHMS_H
