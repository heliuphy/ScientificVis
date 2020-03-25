//
// File: edge.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 21-Mar-2020 11:39:34
//
#ifndef EDGE_H
#define EDGE_H

// Include Files
#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "Canny_types.h"

// Function Declarations
extern void thinAndThreshold(emxArray_boolean_T *E, const emxArray_real32_T *dx,
                             const emxArray_real32_T *dy, const emxArray_real32_T *magGrad, const double
                             lowThresh_data[], const double highThresh_data[], emxArray_boolean_T *H);

#endif

//
// File trailer for edge.h
//
// [EOF]
//
