//
// File: nullAssignment.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 18-Mar-2020 13:12:12
//

// Include Files
#include "rt_nonfinite.h"
#include "CannyAutoThres_X.h"
#include "nullAssignment.h"
#include "CannyAutoThres_X_emxutil.h"

// Function Definitions

//
// Arguments    : emxArray_real_T *x
//                const emxArray_int32_T *idx
// Return Type  : void
//
void nullAssignment(emxArray_real_T *x, const emxArray_int32_T *idx) {
    emxArray_boolean_T *b;
    int nxin;
    int k0;
    int nxout;
    int k;
    emxArray_real_T *b_x;
    emxInit_boolean_T(&b, 2);
    nxin = x->size[0];
    k0 = b->size[0] * b->size[1];
    b->size[0] = 1;
    b->size[1] = x->size[0];
    emxEnsureCapacity((emxArray__common *) b, k0, sizeof(boolean_T));
    nxout = x->size[0];
    for (k0 = 0; k0 < nxout; k0++) {
        b->data[k0] = false;
    }

    for (k = 1; k <= idx->size[0]; k++) {
        b->data[idx->data[k - 1] - 1] = true;
    }

    k0 = 0;
    for (k = 1; k <= b->size[1]; k++) {
        k0 += b->data[k - 1];
    }

    nxout = x->size[0] - k0;
    k0 = -1;
    for (k = 1; k <= nxin; k++) {
        if ((k > b->size[1]) || (!b->data[k - 1])) {
            k0++;
            x->data[k0] = x->data[k - 1];
        }
    }

    emxFree_boolean_T(&b);
    if (1 > nxout) {
        nxout = 0;
    }

    emxInit_real_T(&b_x, 1);
    k0 = b_x->size[0];
    b_x->size[0] = nxout;
    emxEnsureCapacity((emxArray__common *) b_x, k0, sizeof(double));
    for (k0 = 0; k0 < nxout; k0++) {
        b_x->data[k0] = x->data[k0];
    }

    k0 = x->size[0];
    x->size[0] = b_x->size[0];
    emxEnsureCapacity((emxArray__common *) x, k0, sizeof(double));
    nxout = b_x->size[0];
    for (k0 = 0; k0 < nxout; k0++) {
        x->data[k0] = b_x->data[k0];
    }

    emxFree_real_T(&b_x);
}

//
// File trailer for nullAssignment.cpp
//
// [EOF]
//
