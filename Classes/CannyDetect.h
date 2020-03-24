//
// Created by 何柳 on 2020/3/24.
//

#ifndef MYPROJ_CANNYDETECT_H
#define MYPROJ_CANNYDETECT_H

#include <vtkImageData.h>
#include "hlwPlaneAlgorithms.h"

#include "rt_nonfinite.h"
#include "Canny.h"
#include "Canny_terminate.h"
#include "Canny_emxAPI.h"
#include "Canny_initialize.h"


class CannyDetect : public hlwPlaneAlgorithms {
public:
    CannyDetect();

    void run() override;

protected:

    emxArray_real32_T *inputEmxArray;
    emxArray_boolean_T *outputEmxArray;
};


#endif //MYPROJ_CANNYDETECT_H
