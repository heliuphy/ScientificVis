//
// File: edge.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 18-Mar-2020 17:37:36
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
#include "CannyAutoThres_X_types.h"

// Function Declarations
extern void thinAndThreshold(const float dx[320000], const float dy[320000],
  const float magGrad[320000], const double lowThresh_data[], const double
  highThresh_data[], boolean_T H[320000]);

#endif

//
// File trailer for edge.h
//
// [EOF]
//
