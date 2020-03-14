//
// File: imfilter.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 12-Mar-2020 09:21:19
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
#include "CannyAutoThres_types.h"

// Function Declarations
extern void b_imfilter(const float varargin_1[640000], const double varargin_2
[13], float b[640000]);

extern void b_padImage(const float a_tmp[640000], float a[649600]);

extern void imfilter(const float varargin_1[640000], const double varargin_2[13],
                     float b[640000]);

extern void padImage(const float a_tmp[640000], float a[649600]);

#endif

//
// File trailer for imfilter.h
//
// [EOF]
//
