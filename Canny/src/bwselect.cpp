//
// File: bwselect.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 21-Mar-2020 11:39:34
//

// Include Files
#include "rt_nonfinite.h"
#include "Canny.h"
#include "bwselect.h"
#include "Canny_emxutil.h"
#include "imfill.h"
#include "nullAssignment.h"
#include "round.h"

// Function Definitions

//
// Arguments    : const emxArray_boolean_T *varargin_1
//                const emxArray_real_T *varargin_2
//                const emxArray_real_T *varargin_3
//                emxArray_boolean_T *varargout_1
// Return Type  : void
//
void bwselect(const emxArray_boolean_T *varargin_1, const emxArray_real_T
*varargin_2, const emxArray_real_T *varargin_3, emxArray_boolean_T
              *varargout_1) {
    emxArray_real_T *r;
    int i1;
    int idx;
    emxArray_real_T *c;
    boolean_T column_BW;
    boolean_T p;
    emxArray_boolean_T *BW;
    emxArray_real_T *tmp;
    int b_BW;
    emxArray_boolean_T *x;
    int nx;
    emxArray_int32_T *ii;
    boolean_T exitg1;
    emxArray_int32_T *b_tmp;
    emxArray_boolean_T *BW2_temp;
    int siz[2];
    emxArray_int32_T *c_tmp;
    emxArray_real_T *b_r;
    emxInit_real_T(&r, 1);
    i1 = r->size[0];
    r->size[0] = varargin_3->size[0];
    emxEnsureCapacity((emxArray__common *) r, i1, sizeof(double));
    idx = varargin_3->size[0];
    for (i1 = 0; i1 < idx; i1++) {
        r->data[i1] = varargin_3->data[i1];
    }

    emxInit_real_T(&c, 1);
    b_round();
    i1 = c->size[0];
    c->size[0] = varargin_2->size[0];
    emxEnsureCapacity((emxArray__common *) c, i1, sizeof(double));
    idx = varargin_2->size[0];
    for (i1 = 0; i1 < idx; i1++) {
        c->data[i1] = varargin_2->data[i1];
    }

    b_round();
    column_BW = false;
    p = true;
    if (!(varargin_1->size[0] == 1)) {
        p = false;
    }

    if (p) {
        column_BW = true;
    }

    emxInit_boolean_T(&BW, 2);
    emxInit_real_T(&tmp, 1);
    if (column_BW && (varargin_1->size[1] > 1)) {
        column_BW = true;
        i1 = BW->size[0] * BW->size[1];
        BW->size[0] = varargin_1->size[1];
        BW->size[1] = varargin_1->size[0];
        emxEnsureCapacity((emxArray__common *) BW, i1, sizeof(boolean_T));
        idx = varargin_1->size[0];
        for (i1 = 0; i1 < idx; i1++) {
            b_BW = varargin_1->size[1];
            for (nx = 0; nx < b_BW; nx++) {
                BW->data[nx + BW->size[0] * i1] = varargin_1->data[i1 + varargin_1->
                        size[0] * nx];
            }
        }

        i1 = tmp->size[0];
        tmp->size[0] = r->size[0];
        emxEnsureCapacity((emxArray__common *) tmp, i1, sizeof(double));
        idx = r->size[0];
        for (i1 = 0; i1 < idx; i1++) {
            tmp->data[i1] = r->data[i1];
        }

        i1 = r->size[0];
        r->size[0] = c->size[0];
        emxEnsureCapacity((emxArray__common *) r, i1, sizeof(double));
        idx = c->size[0];
        for (i1 = 0; i1 < idx; i1++) {
            r->data[i1] = c->data[i1];
        }

        i1 = c->size[0];
        c->size[0] = tmp->size[0];
        emxEnsureCapacity((emxArray__common *) c, i1, sizeof(double));
        idx = tmp->size[0];
        for (i1 = 0; i1 < idx; i1++) {
            c->data[i1] = tmp->data[i1];
        }
    } else {
        column_BW = false;
        i1 = BW->size[0] * BW->size[1];
        BW->size[0] = varargin_1->size[0];
        BW->size[1] = varargin_1->size[1];
        emxEnsureCapacity((emxArray__common *) BW, i1, sizeof(boolean_T));
        idx = varargin_1->size[0] * varargin_1->size[1];
        for (i1 = 0; i1 < idx; i1++) {
            BW->data[i1] = varargin_1->data[i1];
        }
    }

    emxInit_boolean_T1(&x, 1);
    nx = BW->size[0];
    b_BW = BW->size[1];
    i1 = x->size[0];
    x->size[0] = r->size[0];
    emxEnsureCapacity((emxArray__common *) x, i1, sizeof(boolean_T));
    idx = r->size[0];
    for (i1 = 0; i1 < idx; i1++) {
        x->data[i1] = ((r->data[i1] < 1.0) || (r->data[i1] > nx) || (c->data[i1] <
                                                                     1.0) || (c->data[i1] > b_BW));
    }

    emxInit_int32_T1(&ii, 1);
    nx = x->size[0];
    idx = 0;
    i1 = ii->size[0];
    ii->size[0] = x->size[0];
    emxEnsureCapacity((emxArray__common *) ii, i1, sizeof(int));
    b_BW = 1;
    exitg1 = false;
    while ((!exitg1) && (b_BW <= nx)) {
        if (x->data[b_BW - 1]) {
            idx++;
            ii->data[idx - 1] = b_BW;
            if (idx >= nx) {
                exitg1 = true;
            } else {
                b_BW++;
            }
        } else {
            b_BW++;
        }
    }

    if (x->size[0] == 1) {
        if (idx == 0) {
            i1 = ii->size[0];
            ii->size[0] = 0;
            emxEnsureCapacity((emxArray__common *) ii, i1, sizeof(int));
        }
    } else {
        i1 = ii->size[0];
        if (1 > idx) {
            ii->size[0] = 0;
        } else {
            ii->size[0] = idx;
        }

        emxEnsureCapacity((emxArray__common *) ii, i1, sizeof(int));
    }

    emxFree_boolean_T(&x);
    i1 = tmp->size[0];
    tmp->size[0] = ii->size[0];
    emxEnsureCapacity((emxArray__common *) tmp, i1, sizeof(double));
    idx = ii->size[0];
    for (i1 = 0; i1 < idx; i1++) {
        tmp->data[i1] = ii->data[i1];
    }

    emxFree_int32_T(&ii);
    if (!(tmp->size[0] == 0)) {
        emxInit_int32_T1(&b_tmp, 1);
        i1 = b_tmp->size[0];
        b_tmp->size[0] = tmp->size[0];
        emxEnsureCapacity((emxArray__common *) b_tmp, i1, sizeof(int));
        idx = tmp->size[0];
        for (i1 = 0; i1 < idx; i1++) {
            b_tmp->data[i1] = (int) tmp->data[i1];
        }

        emxInit_int32_T1(&c_tmp, 1);
        nullAssignment(r, b_tmp);
        i1 = c_tmp->size[0];
        c_tmp->size[0] = tmp->size[0];
        emxEnsureCapacity((emxArray__common *) c_tmp, i1, sizeof(int));
        idx = tmp->size[0];
        emxFree_int32_T(&b_tmp);
        for (i1 = 0; i1 < idx; i1++) {
            c_tmp->data[i1] = (int) tmp->data[i1];
        }

        nullAssignment(c, c_tmp);
        emxFree_int32_T(&c_tmp);
    }

    emxFree_real_T(&tmp);
    for (i1 = 0; i1 < 2; i1++) {
        siz[i1] = BW->size[i1];
    }

    emxInit_boolean_T(&BW2_temp, 2);
    i1 = BW2_temp->size[0] * BW2_temp->size[1];
    BW2_temp->size[0] = BW->size[0];
    BW2_temp->size[1] = BW->size[1];
    emxEnsureCapacity((emxArray__common *) BW2_temp, i1, sizeof(boolean_T));
    idx = BW->size[0] * BW->size[1];
    for (i1 = 0; i1 < idx; i1++) {
        BW2_temp->data[i1] = !BW->data[i1];
    }

    emxInit_real_T(&b_r, 1);
    i1 = b_r->size[0];
    b_r->size[0] = r->size[0];
    emxEnsureCapacity((emxArray__common *) b_r, i1, sizeof(double));
    idx = r->size[0];
    for (i1 = 0; i1 < idx; i1++) {
        b_r->data[i1] = (int) r->data[i1] + siz[0] * ((int) c->data[i1] - 1);
    }

    emxFree_real_T(&c);
    emxFree_real_T(&r);
    imfill(BW2_temp, b_r);
    i1 = BW2_temp->size[0] * BW2_temp->size[1];
    emxEnsureCapacity((emxArray__common *) BW2_temp, i1, sizeof(boolean_T));
    b_BW = BW2_temp->size[0];
    nx = BW2_temp->size[1];
    idx = b_BW * nx;
    emxFree_real_T(&b_r);
    for (i1 = 0; i1 < idx; i1++) {
        BW2_temp->data[i1] = (BW2_temp->data[i1] && BW->data[i1]);
    }

    emxFree_boolean_T(&BW);
    if (column_BW) {
        i1 = varargout_1->size[0] * varargout_1->size[1];
        varargout_1->size[0] = BW2_temp->size[1];
        varargout_1->size[1] = BW2_temp->size[0];
        emxEnsureCapacity((emxArray__common *) varargout_1, i1, sizeof(boolean_T));
        idx = BW2_temp->size[0];
        for (i1 = 0; i1 < idx; i1++) {
            b_BW = BW2_temp->size[1];
            for (nx = 0; nx < b_BW; nx++) {
                varargout_1->data[nx + varargout_1->size[0] * i1] = BW2_temp->data[i1 +
                                                                                   BW2_temp->size[0] * nx];
            }
        }
    } else {
        i1 = varargout_1->size[0] * varargout_1->size[1];
        varargout_1->size[0] = BW2_temp->size[0];
        varargout_1->size[1] = BW2_temp->size[1];
        emxEnsureCapacity((emxArray__common *) varargout_1, i1, sizeof(boolean_T));
        idx = BW2_temp->size[0] * BW2_temp->size[1];
        for (i1 = 0; i1 < idx; i1++) {
            varargout_1->data[i1] = BW2_temp->data[i1];
        }
    }

    emxFree_boolean_T(&BW2_temp);
}

//
// File trailer for bwselect.cpp
//
// [EOF]
//
