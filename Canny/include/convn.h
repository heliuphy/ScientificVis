//
// File: convn.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 12-Mar-2020 09:21:19
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
#include "CannyAutoThres_types.h"

// Function Declarations
extern void b_convn(const float A[649600], const float B[13], float C[640000]);

extern void convn(const float A[649600], const float B[13], float C[640000]);

#endif

//
// File trailer for convn.h
//
// [EOF]
//
