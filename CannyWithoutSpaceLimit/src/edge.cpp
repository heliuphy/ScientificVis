//
// File: edge.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 18-Mar-2020 13:12:12
//

// Include Files
#include "rt_nonfinite.h"
#include "CannyAutoThres_X.h"
#include "edge.h"
#include "CannyAutoThres_X_emxutil.h"
#include "bwselect.h"
#include "libmwcannythresholding_tbb.h"

// Function Definitions

//
// Arguments    : emxArray_boolean_T *E
//                const emxArray_real32_T *dx
//                const emxArray_real32_T *dy
//                const emxArray_real32_T *magGrad
//                const double lowThresh_data[]
//                const double highThresh_data[]
//                emxArray_boolean_T *H
// Return Type  : void
//
void thinAndThreshold(emxArray_boolean_T *E, const emxArray_real32_T *dx, const
emxArray_real32_T *dy, const emxArray_real32_T *magGrad,
                      const double lowThresh_data[], const double
                      highThresh_data[], emxArray_boolean_T *H) {
    emxArray_boolean_T *x;
    int n;
    int m;
    double sz[2];
    int jj;
    int ii;
    emxArray_int32_T *b_ii;
    emxArray_int32_T *b_jj;
    int nx;
    int idx;
    boolean_T exitg1;
    boolean_T guard1 = false;
    emxArray_real_T *idxStrongC;
    emxArray_real_T *c_ii;
    emxInit_boolean_T(&x, 2);
    n = E->size[1];
    m = E->size[0];
    sz[0] = (unsigned int) E->size[0];
    sz[1] = (unsigned int) E->size[1];
    cannythresholding_real32_tbb(&dx->data[0], &dy->data[0], &magGrad->data[0], sz,
                                 lowThresh_data[0], &E->data[0]);
    jj = x->size[0] * x->size[1];
    x->size[0] = magGrad->size[0];
    x->size[1] = magGrad->size[1];
    emxEnsureCapacity((emxArray__common *) x, jj, sizeof(boolean_T));
    ii = magGrad->size[0] * magGrad->size[1];
    for (jj = 0; jj < ii; jj++) {
        x->data[jj] = ((magGrad->data[jj] > highThresh_data[0]) && E->data[jj]);
    }

    emxInit_int32_T1(&b_ii, 1);
    emxInit_int32_T1(&b_jj, 1);
    nx = x->size[0] * x->size[1];
    idx = 0;
    jj = b_ii->size[0];
    b_ii->size[0] = nx;
    emxEnsureCapacity((emxArray__common *) b_ii, jj, sizeof(int));
    jj = b_jj->size[0];
    b_jj->size[0] = nx;
    emxEnsureCapacity((emxArray__common *) b_jj, jj, sizeof(int));
    if (nx == 0) {
        jj = b_ii->size[0];
        b_ii->size[0] = 0;
        emxEnsureCapacity((emxArray__common *) b_ii, jj, sizeof(int));
        jj = b_jj->size[0];
        b_jj->size[0] = 0;
        emxEnsureCapacity((emxArray__common *) b_jj, jj, sizeof(int));
    } else {
        ii = 1;
        jj = 1;
        exitg1 = false;
        while ((!exitg1) && (jj <= x->size[1])) {
            guard1 = false;
            if (x->data[(ii + x->size[0] * (jj - 1)) - 1]) {
                idx++;
                b_ii->data[idx - 1] = ii;
                b_jj->data[idx - 1] = jj;
                if (idx >= nx) {
                    exitg1 = true;
                } else {
                    guard1 = true;
                }
            } else {
                guard1 = true;
            }

            if (guard1) {
                ii++;
                if (ii > x->size[0]) {
                    ii = 1;
                    jj++;
                }
            }
        }

        if (nx == 1) {
            if (idx == 0) {
                jj = b_ii->size[0];
                b_ii->size[0] = 0;
                emxEnsureCapacity((emxArray__common *) b_ii, jj, sizeof(int));
                jj = b_jj->size[0];
                b_jj->size[0] = 0;
                emxEnsureCapacity((emxArray__common *) b_jj, jj, sizeof(int));
            }
        } else {
            jj = b_ii->size[0];
            if (1 > idx) {
                b_ii->size[0] = 0;
            } else {
                b_ii->size[0] = idx;
            }

            emxEnsureCapacity((emxArray__common *) b_ii, jj, sizeof(int));
            jj = b_jj->size[0];
            if (1 > idx) {
                b_jj->size[0] = 0;
            } else {
                b_jj->size[0] = idx;
            }

            emxEnsureCapacity((emxArray__common *) b_jj, jj, sizeof(int));
        }
    }

    emxFree_boolean_T(&x);
    emxInit_real_T(&idxStrongC, 1);
    jj = idxStrongC->size[0];
    idxStrongC->size[0] = b_jj->size[0];
    emxEnsureCapacity((emxArray__common *) idxStrongC, jj, sizeof(double));
    ii = b_jj->size[0];
    for (jj = 0; jj < ii; jj++) {
        idxStrongC->data[jj] = b_jj->data[jj];
    }

    emxFree_int32_T(&b_jj);
    if (!(idxStrongC->size[0] == 0)) {
        emxInit_real_T(&c_ii, 1);
        jj = c_ii->size[0];
        c_ii->size[0] = b_ii->size[0];
        emxEnsureCapacity((emxArray__common *) c_ii, jj, sizeof(double));
        ii = b_ii->size[0];
        for (jj = 0; jj < ii; jj++) {
            c_ii->data[jj] = b_ii->data[jj];
        }

        bwselect(E, idxStrongC, c_ii, H);
        emxFree_real_T(&c_ii);
    } else {
        jj = H->size[0] * H->size[1];
        H->size[0] = m;
        H->size[1] = n;
        emxEnsureCapacity((emxArray__common *) H, jj, sizeof(boolean_T));
        ii = m * n;
        for (jj = 0; jj < ii; jj++) {
            H->data[jj] = false;
        }
    }

    emxFree_int32_T(&b_ii);
    emxFree_real_T(&idxStrongC);
}

//
// File trailer for edge.cpp
//
// [EOF]
//
