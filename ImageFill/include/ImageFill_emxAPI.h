//
// File: ImageFill_emxAPI.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 21-Mar-2020 11:42:13
//
#ifndef IMAGEFILL_EMXAPI_H
#define IMAGEFILL_EMXAPI_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "ImageFill_types.h"

// Function Declarations
extern emxArray_real_T *emxCreateND_real_T(int numDimensions, int *size);

extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows, int cols);

extern emxArray_boolean_T *emxCreate_boolean_T(int rows, int cols);

extern emxArray_real_T *emxCreate_real_T(int rows, int cols);

extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);

extern void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

//
// File trailer for ImageFill_emxAPI.h
//
// [EOF]
//
