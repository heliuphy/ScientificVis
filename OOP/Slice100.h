//
// Created by 何柳 on 2020/3/21.
//

#ifndef MYPROJ_SLICE100_H
#define MYPROJ_SLICE100_H

#include "AlgoBase.h"

class Slice100 : public AlgoBase {
public:
    Slice100(int zStart,
             int zEnd,
             int planeSpacing,
             vtkImageData *_input2dImageData,
             vtkImageData *_input3dImageData);

    void printOriginalSlice();

    void printCannySlice();

    void printAfterSubSlice();

};


#endif //MYPROJ_SLICE100_H
