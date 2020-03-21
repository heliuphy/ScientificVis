//
// Created by 何柳 on 2020/3/21.
//

#ifndef MYPROJ_GENERATE3D_H
#define MYPROJ_GENERATE3D_H

#include "AlgoBase.h"

class Generate3d : public AlgoBase {
public:
    Generate3d(int zStart,
               int zEnd,
               int planeSpacing,
               vtkImageData *_input2dImageData,
               vtkImageData *_input3dImageData);

    void generate3D();
};


#endif //MYPROJ_GENERATE3D_H
