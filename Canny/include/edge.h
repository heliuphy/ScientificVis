//
// File: edge.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 12-Mar-2020 09:21:19
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
#include "CannyAutoThres_types.h"

// Function Declarations
extern void thinAndThreshold(boolean_T E[640000], const float dx[640000], const
float dy[640000], const float magGrad[640000], const double lowThresh_data[],
                             const double highThresh_data[], boolean_T H[640000]);

#endif

//
// File trailer for edge.h
//
// [EOF]
//
