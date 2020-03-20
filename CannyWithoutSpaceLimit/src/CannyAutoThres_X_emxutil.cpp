//
// File: CannyAutoThres_X_emxutil.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 18-Mar-2020 13:12:12
//

// Include Files
#include "rt_nonfinite.h"
#include "CannyAutoThres_X.h"
#include "CannyAutoThres_X_emxutil.h"

// Function Definitions

//
// Arguments    : emxArray__common *emxArray
//                int oldNumel
//                unsigned int elementSize
// Return Type  : void
//
void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, unsigned int
elementSize) {
    int newNumel;
    int i;
    void *newData;
    if (oldNumel < 0) {
        oldNumel = 0;
    }

    newNumel = 1;
    for (i = 0; i < emxArray->numDimensions; i++) {
        newNumel *= emxArray->size[i];
    }

    if (newNumel > emxArray->allocatedSize) {
        i = emxArray->allocatedSize;
        if (i < 16) {
            i = 16;
        }

        while (i < newNumel) {
            if (i > 1073741823) {
                i = MAX_int32_T;
            } else {
                i <<= 1;
            }
        }

        newData = calloc((unsigned int) i, elementSize);
        if (emxArray->data != NULL) {
            memcpy(newData, emxArray->data, elementSize * oldNumel);
            if (emxArray->canFreeData) {
                free(emxArray->data);
            }
        }

        emxArray->data = newData;
        emxArray->allocatedSize = i;
        emxArray->canFreeData = true;
    }
}

//
// Arguments    : emxArray_boolean_T **pEmxArray
// Return Type  : void
//
void emxFree_boolean_T(emxArray_boolean_T **pEmxArray) {
    if (*pEmxArray != (emxArray_boolean_T *) NULL) {
        if (((*pEmxArray)->data != (boolean_T *) NULL) && (*pEmxArray)->canFreeData) {
            free((void *) (*pEmxArray)->data);
        }

        free((void *) (*pEmxArray)->size);
        free((void *) *pEmxArray);
        *pEmxArray = (emxArray_boolean_T *) NULL;
    }
}

//
// Arguments    : emxArray_int32_T **pEmxArray
// Return Type  : void
//
void emxFree_int32_T(emxArray_int32_T **pEmxArray) {
    if (*pEmxArray != (emxArray_int32_T *) NULL) {
        if (((*pEmxArray)->data != (int *) NULL) && (*pEmxArray)->canFreeData) {
            free((void *) (*pEmxArray)->data);
        }

        free((void *) (*pEmxArray)->size);
        free((void *) *pEmxArray);
        *pEmxArray = (emxArray_int32_T *) NULL;
    }
}

//
// Arguments    : emxArray_real32_T **pEmxArray
// Return Type  : void
//
void emxFree_real32_T(emxArray_real32_T **pEmxArray) {
    if (*pEmxArray != (emxArray_real32_T *) NULL) {
        if (((*pEmxArray)->data != (float *) NULL) && (*pEmxArray)->canFreeData) {
            free((void *) (*pEmxArray)->data);
        }

        free((void *) (*pEmxArray)->size);
        free((void *) *pEmxArray);
        *pEmxArray = (emxArray_real32_T *) NULL;
    }
}

//
// Arguments    : emxArray_real_T **pEmxArray
// Return Type  : void
//
void emxFree_real_T(emxArray_real_T **pEmxArray) {
    if (*pEmxArray != (emxArray_real_T *) NULL) {
        if (((*pEmxArray)->data != (double *) NULL) && (*pEmxArray)->canFreeData) {
            free((void *) (*pEmxArray)->data);
        }

        free((void *) (*pEmxArray)->size);
        free((void *) *pEmxArray);
        *pEmxArray = (emxArray_real_T *) NULL;
    }
}

//
// Arguments    : emxArray_uint32_T **pEmxArray
// Return Type  : void
//
void emxFree_uint32_T(emxArray_uint32_T **pEmxArray) {
    if (*pEmxArray != (emxArray_uint32_T *) NULL) {
        if (((*pEmxArray)->data != (unsigned int *) NULL) && (*pEmxArray)
                ->canFreeData) {
            free((void *) (*pEmxArray)->data);
        }

        free((void *) (*pEmxArray)->size);
        free((void *) *pEmxArray);
        *pEmxArray = (emxArray_uint32_T *) NULL;
    }
}

//
// Arguments    : emxArray_boolean_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int numDimensions) {
    emxArray_boolean_T *emxArray;
    int i;
    *pEmxArray = (emxArray_boolean_T *) malloc(sizeof(emxArray_boolean_T));
    emxArray = *pEmxArray;
    emxArray->data = (boolean_T *) NULL;
    emxArray->numDimensions = numDimensions;
    emxArray->size = (int *) malloc((unsigned int) (sizeof(int) * numDimensions));
    emxArray->allocatedSize = 0;
    emxArray->canFreeData = true;
    for (i = 0; i < numDimensions; i++) {
        emxArray->size[i] = 0;
    }
}

//
// Arguments    : emxArray_boolean_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_boolean_T1(emxArray_boolean_T **pEmxArray, int numDimensions) {
    emxArray_boolean_T *emxArray;
    int i;
    *pEmxArray = (emxArray_boolean_T *) malloc(sizeof(emxArray_boolean_T));
    emxArray = *pEmxArray;
    emxArray->data = (boolean_T *) NULL;
    emxArray->numDimensions = numDimensions;
    emxArray->size = (int *) malloc((unsigned int) (sizeof(int) * numDimensions));
    emxArray->allocatedSize = 0;
    emxArray->canFreeData = true;
    for (i = 0; i < numDimensions; i++) {
        emxArray->size[i] = 0;
    }
}

//
// Arguments    : emxArray_int32_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions) {
    emxArray_int32_T *emxArray;
    int i;
    *pEmxArray = (emxArray_int32_T *) malloc(sizeof(emxArray_int32_T));
    emxArray = *pEmxArray;
    emxArray->data = (int *) NULL;
    emxArray->numDimensions = numDimensions;
    emxArray->size = (int *) malloc((unsigned int) (sizeof(int) * numDimensions));
    emxArray->allocatedSize = 0;
    emxArray->canFreeData = true;
    for (i = 0; i < numDimensions; i++) {
        emxArray->size[i] = 0;
    }
}

//
// Arguments    : emxArray_int32_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_int32_T1(emxArray_int32_T **pEmxArray, int numDimensions) {
    emxArray_int32_T *emxArray;
    int i;
    *pEmxArray = (emxArray_int32_T *) malloc(sizeof(emxArray_int32_T));
    emxArray = *pEmxArray;
    emxArray->data = (int *) NULL;
    emxArray->numDimensions = numDimensions;
    emxArray->size = (int *) malloc((unsigned int) (sizeof(int) * numDimensions));
    emxArray->allocatedSize = 0;
    emxArray->canFreeData = true;
    for (i = 0; i < numDimensions; i++) {
        emxArray->size[i] = 0;
    }
}

//
// Arguments    : emxArray_real32_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_real32_T(emxArray_real32_T **pEmxArray, int numDimensions) {
    emxArray_real32_T *emxArray;
    int i;
    *pEmxArray = (emxArray_real32_T *) malloc(sizeof(emxArray_real32_T));
    emxArray = *pEmxArray;
    emxArray->data = (float *) NULL;
    emxArray->numDimensions = numDimensions;
    emxArray->size = (int *) malloc((unsigned int) (sizeof(int) * numDimensions));
    emxArray->allocatedSize = 0;
    emxArray->canFreeData = true;
    for (i = 0; i < numDimensions; i++) {
        emxArray->size[i] = 0;
    }
}

//
// Arguments    : emxArray_real_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions) {
    emxArray_real_T *emxArray;
    int i;
    *pEmxArray = (emxArray_real_T *) malloc(sizeof(emxArray_real_T));
    emxArray = *pEmxArray;
    emxArray->data = (double *) NULL;
    emxArray->numDimensions = numDimensions;
    emxArray->size = (int *) malloc((unsigned int) (sizeof(int) * numDimensions));
    emxArray->allocatedSize = 0;
    emxArray->canFreeData = true;
    for (i = 0; i < numDimensions; i++) {
        emxArray->size[i] = 0;
    }
}

//
// Arguments    : emxArray_uint32_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_uint32_T(emxArray_uint32_T **pEmxArray, int numDimensions) {
    emxArray_uint32_T *emxArray;
    int i;
    *pEmxArray = (emxArray_uint32_T *) malloc(sizeof(emxArray_uint32_T));
    emxArray = *pEmxArray;
    emxArray->data = (unsigned int *) NULL;
    emxArray->numDimensions = numDimensions;
    emxArray->size = (int *) malloc((unsigned int) (sizeof(int) * numDimensions));
    emxArray->allocatedSize = 0;
    emxArray->canFreeData = true;
    for (i = 0; i < numDimensions; i++) {
        emxArray->size[i] = 0;
    }
}

//
// File trailer for CannyAutoThres_X_emxutil.cpp
//
// [EOF]
//
