//
// File: imfilter.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 18-Mar-2020 17:37:36
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
extern void b_imfilter(const float varargin_1[320000], const double varargin_2
  [13], float b[320000]);
extern void b_padImage(const float a_tmp[320000], float a[329600]);
extern void imfilter(const float varargin_1[320000], const double varargin_2[13],
                     float b[320000]);
extern void padImage(const float a_tmp[320000], float a[324800]);

#endif

//
// File trailer for imfilter.h
//
// [EOF]
//
