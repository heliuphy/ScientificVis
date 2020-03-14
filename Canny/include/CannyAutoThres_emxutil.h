//
// File: CannyAutoThres_emxutil.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 12-Mar-2020 09:21:19
//
#ifndef CANNYAUTOTHRES_EMXUTIL_H
#define CANNYAUTOTHRES_EMXUTIL_H

// Include Files
#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "CannyAutoThres_types.h"

// Function Declarations
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, unsigned
int elementSize);

extern void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);

extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);

extern void emxFree_real_T(emxArray_real_T **pEmxArray);

extern void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int numDimensions);

extern void emxInit_boolean_T1(emxArray_boolean_T **pEmxArray, int numDimensions);

extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);

extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

//
// File trailer for CannyAutoThres_emxutil.h
//
// [EOF]
//
