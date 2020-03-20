//
// File: convn.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 18-Mar-2020 17:37:36
//
#ifndef CONVN_H
#define CONVN_H

// Include Files
#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "CannyAutoThres_X_types.h"

// Function Declarations
extern void b_convn(const float A[329600], const float B[13], float C[320000]);
extern void convn(const float A[324800], const float B[13], float C[320000]);

#endif

//
// File trailer for convn.h
//
// [EOF]
//
