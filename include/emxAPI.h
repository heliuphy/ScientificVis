//
// Created by 何柳 on 2020/3/24.
//

#ifndef MYPROJ_EMXAPI_H
#define MYPROJ_EMXAPI_H

#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "Canny_types.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "ImageFill_types.h"

// Function Declarations
extern emxArray_boolean_T *emxCreateND_boolean_T(int numDimensions, int *size);

extern emxArray_real32_T *emxCreateND_real32_T(int numDimensions, int *size);

extern emxArray_boolean_T *emxCreateWrapperND_boolean_T(boolean_T *data, int
numDimensions, int *size);

extern emxArray_real32_T *emxCreateWrapperND_real32_T(float *data, int
numDimensions, int *size);

extern emxArray_boolean_T *emxCreateWrapper_boolean_T(boolean_T *data, int rows,
                                                      int cols);

extern emxArray_real32_T *emxCreateWrapper_real32_T(float *data, int rows, int
cols);

extern emxArray_boolean_T *emxCreate_boolean_T(int rows, int cols);

extern emxArray_real32_T *emxCreate_real32_T(int rows, int cols);

extern void emxDestroyArray_boolean_T(emxArray_boolean_T *emxArray);

extern void emxDestroyArray_real32_T(emxArray_real32_T *emxArray);

extern void emxInitArray_boolean_T(emxArray_boolean_T **pEmxArray, int
numDimensions);

extern void emxInitArray_real32_T(emxArray_real32_T **pEmxArray, int
numDimensions);


// Function Declarations
extern emxArray_boolean_T *emxCreateND_boolean_T(int numDimensions, int *size);

extern emxArray_real_T *emxCreateND_real_T(int numDimensions, int *size);

extern emxArray_boolean_T *emxCreateWrapperND_boolean_T(boolean_T *data, int
numDimensions, int *size);

extern emxArray_real_T *emxCreateWrapperND_real_T(double *data, int
numDimensions, int *size);

extern emxArray_boolean_T *emxCreateWrapper_boolean_T(boolean_T *data, int rows,
                                                      int cols);

extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows, int cols);

extern emxArray_boolean_T *emxCreate_boolean_T(int rows, int cols);

extern emxArray_real_T *emxCreate_real_T(int rows, int cols);

extern void emxDestroyArray_boolean_T(emxArray_boolean_T *emxArray);

extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);

extern void emxInitArray_boolean_T(emxArray_boolean_T **pEmxArray, int
numDimensions);

extern void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif //MYPROJ_EMXAPI_H
