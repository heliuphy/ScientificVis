//
// Created by 何柳 on 2020/3/24.
//

#ifndef MYPROJ_HLWIMAGEFILL_H
#define MYPROJ_HLWIMAGEFILL_H

#include <vtkImageData.h>
#include "hlwPlaneAlgorithms.h"

#include "rt_nonfinite.h"
#include "Canny.h"
#include "Canny_terminate.h"
#include "Canny_emxAPI.h"
#include "Canny_initialize.h"
#include "ImageFill.h"
#include "ImageFill_emxAPI.h"
#include "ImageFill_emxutil.h"
#include "ImageFill_initialize.h"
#include "ImageFill_types.h"


class hlwImageFill : public hlwPlaneAlgorithms {
public:
    hlwImageFill();

    void run() override;

    void setFillPoints(real_T *_points, int len);

    void findPointIDToImfill(double *p1, double *p2);

    void findAllIntersectionPoints(double *_p, int *_num);
protected:
    emxArray_boolean_T *inputEmxArray;
    emxArray_boolean_T *outputEmxArray;
    emxArray_real_T *pointIdArray;
};


#endif //MYPROJ_HLWIMAGEFILL_H
