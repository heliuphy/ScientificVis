//
// Created by 何柳 on 2020/3/24.
//

#ifndef MYPROJ_HLWIMAGEMATH_H
#define MYPROJ_HLWIMAGEMATH_H

#define HLW_SUB 0
#define HLW_MULTI_K 1

#include "hlwPlaneAlgorithms.h"
#include <vtkImageData.h>

class hlwImageMath : public hlwPlaneAlgorithms {

public:

    hlwImageMath();

    void setInputImageData2(vtkImageData*);

    void setOperatorToSub();

    void setOperatorToMultiplyK(int k);

    void run() override;

protected:
    void subTwoUnCharImageArray();

    void array1MultiplyByK();

protected:
    vtkImageData *inputImageData2;
    int oper;
    int k;
};


#endif //myproj_hlwimagemath_h
