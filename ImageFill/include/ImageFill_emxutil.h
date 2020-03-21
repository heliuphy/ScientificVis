//
// File: ImageFill_emxutil.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 21-Mar-2020 11:42:13
//
#ifndef IMAGEFILL_EMXUTIL_H
#define IMAGEFILL_EMXUTIL_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "ImageFill_types.h"

// Function Declarations
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, unsigned
int elementSize);

extern void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);

extern void emxFree_real_T(emxArray_real_T **pEmxArray);

extern void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int numDimensions);

extern void emxInit_boolean_T1(emxArray_boolean_T **pEmxArray, int numDimensions);

extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

//
// File trailer for ImageFill_emxutil.h
//
// [EOF]
//
