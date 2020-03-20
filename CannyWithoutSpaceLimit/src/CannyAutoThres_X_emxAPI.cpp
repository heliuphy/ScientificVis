//
// File: CannyAutoThres_X_emxAPI.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 18-Mar-2020 13:12:12
//

// Include Files
#include "rt_nonfinite.h"
#include "CannyAutoThres_X.h"
#include "CannyAutoThres_X_emxAPI.h"
#include "CannyAutoThres_X_emxutil.h"

// Function Definitions

//
// Arguments    : int numDimensions
//                int *size
// Return Type  : emxArray_boolean_T *
//
emxArray_boolean_T *emxCreateND_boolean_T(int numDimensions, int *size) {
    emxArray_boolean_T *emx;
    int numEl;
    int i;
    emxInit_boolean_T(&emx, numDimensions);
    numEl = 1;
    for (i = 0; i < numDimensions; i++) {
        numEl *= size[i];
        emx->size[i] = size[i];
    }

    emx->data = (boolean_T *) calloc((unsigned int) numEl, sizeof(boolean_T));
    emx->numDimensions = numDimensions;
    emx->allocatedSize = numEl;
    return emx;
}

//
// Arguments    : int numDimensions
//                int *size
// Return Type  : emxArray_real32_T *
//
emxArray_real32_T *emxCreateND_real32_T(int numDimensions, int *size) {
    emxArray_real32_T *emx;
    int numEl;
    int i;
    emxInit_real32_T(&emx, numDimensions);
    numEl = 1;
    for (i = 0; i < numDimensions; i++) {
        numEl *= size[i];
        emx->size[i] = size[i];
    }

    emx->data = (float *) calloc((unsigned int) numEl, sizeof(float));
    emx->numDimensions = numDimensions;
    emx->allocatedSize = numEl;
    return emx;
}

//
// Arguments    : boolean_T *data
//                int numDimensions
//                int *size
// Return Type  : emxArray_boolean_T *
//
emxArray_boolean_T *emxCreateWrapperND_boolean_T(boolean_T *data, int
numDimensions, int *size) {
    emxArray_boolean_T *emx;
    int numEl;
    int i;
    emxInit_boolean_T(&emx, numDimensions);
    numEl = 1;
    for (i = 0; i < numDimensions; i++) {
        numEl *= size[i];
        emx->size[i] = size[i];
    }

    emx->data = data;
    emx->numDimensions = numDimensions;
    emx->allocatedSize = numEl;
    emx->canFreeData = false;
    return emx;
}

//
// Arguments    : float *data
//                int numDimensions
//                int *size
// Return Type  : emxArray_real32_T *
//
emxArray_real32_T *emxCreateWrapperND_real32_T(float *data, int numDimensions,
                                               int *size) {
    emxArray_real32_T *emx;
    int numEl;
    int i;
    emxInit_real32_T(&emx, numDimensions);
    numEl = 1;
    for (i = 0; i < numDimensions; i++) {
        numEl *= size[i];
        emx->size[i] = size[i];
    }

    emx->data = data;
    emx->numDimensions = numDimensions;
    emx->allocatedSize = numEl;
    emx->canFreeData = false;
    return emx;
}

//
// Arguments    : boolean_T *data
//                int rows
//                int cols
// Return Type  : emxArray_boolean_T *
//
emxArray_boolean_T *emxCreateWrapper_boolean_T(boolean_T *data, int rows, int
cols) {
    emxArray_boolean_T *emx;
    int size[2];
    int numEl;
    int i;
    size[0] = rows;
    size[1] = cols;
    emxInit_boolean_T(&emx, 2);
    numEl = 1;
    for (i = 0; i < 2; i++) {
        numEl *= size[i];
        emx->size[i] = size[i];
    }

    emx->data = data;
    emx->numDimensions = 2;
    emx->allocatedSize = numEl;
    emx->canFreeData = false;
    return emx;
}

//
// Arguments    : float *data
//                int rows
//                int cols
// Return Type  : emxArray_real32_T *
//
emxArray_real32_T *emxCreateWrapper_real32_T(float *data, int rows, int cols) {
    emxArray_real32_T *emx;
    int size[2];
    int numEl;
    int i;
    size[0] = rows;
    size[1] = cols;
    emxInit_real32_T(&emx, 2);
    numEl = 1;
    for (i = 0; i < 2; i++) {
        numEl *= size[i];
        emx->size[i] = size[i];
    }

    emx->data = data;
    emx->numDimensions = 2;
    emx->allocatedSize = numEl;
    emx->canFreeData = false;
    return emx;
}

//
// Arguments    : int rows
//                int cols
// Return Type  : emxArray_boolean_T *
//
emxArray_boolean_T *emxCreate_boolean_T(int rows, int cols) {
    emxArray_boolean_T *emx;
    int size[2];
    int numEl;
    int i;
    size[0] = rows;
    size[1] = cols;
    emxInit_boolean_T(&emx, 2);
    numEl = 1;
    for (i = 0; i < 2; i++) {
        numEl *= size[i];
        emx->size[i] = size[i];
    }

    emx->data = (boolean_T *) calloc((unsigned int) numEl, sizeof(boolean_T));
    emx->numDimensions = 2;
    emx->allocatedSize = numEl;
    return emx;
}

//
// Arguments    : int rows
//                int cols
// Return Type  : emxArray_real32_T *
//
emxArray_real32_T *emxCreate_real32_T(int rows, int cols) {
    emxArray_real32_T *emx;
    int size[2];
    int numEl;
    int i;
    size[0] = rows;
    size[1] = cols;
    emxInit_real32_T(&emx, 2);
    numEl = 1;
    for (i = 0; i < 2; i++) {
        numEl *= size[i];
        emx->size[i] = size[i];
    }

    emx->data = (float *) calloc((unsigned int) numEl, sizeof(float));
    emx->numDimensions = 2;
    emx->allocatedSize = numEl;
    return emx;
}

//
// Arguments    : emxArray_boolean_T *emxArray
// Return Type  : void
//
void emxDestroyArray_boolean_T(emxArray_boolean_T *emxArray) {
    emxFree_boolean_T(&emxArray);
}

//
// Arguments    : emxArray_real32_T *emxArray
// Return Type  : void
//
void emxDestroyArray_real32_T(emxArray_real32_T *emxArray) {
    emxFree_real32_T(&emxArray);
}

//
// Arguments    : emxArray_boolean_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInitArray_boolean_T(emxArray_boolean_T **pEmxArray, int numDimensions) {
    emxInit_boolean_T(pEmxArray, numDimensions);
}

//
// Arguments    : emxArray_real32_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInitArray_real32_T(emxArray_real32_T **pEmxArray, int numDimensions) {
    emxInit_real32_T(pEmxArray, numDimensions);
}

//
// File trailer for CannyAutoThres_X_emxAPI.cpp
//
// [EOF]
//
