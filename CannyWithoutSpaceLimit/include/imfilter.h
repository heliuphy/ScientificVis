//
// File: imfilter.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 18-Mar-2020 13:12:12
//
#ifndef IMFILTER_H
#define IMFILTER_H

// Include Files
#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "CannyAutoThres_X_types.h"

// Function Declarations
extern void b_imfilter(emxArray_real32_T *varargin_1, const double varargin_2[13]);

extern void imfilter(emxArray_real32_T *varargin_1);

extern void padImage(const emxArray_real32_T *a_tmp, const double pad[2],
                     emxArray_real32_T *a);

#endif

//
// File trailer for imfilter.h
//
// [EOF]
//
