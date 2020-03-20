//
// File: bwselect.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 18-Mar-2020 17:37:36
//

// Include Files
#include "rt_nonfinite.h"
#include "CannyAutoThres_X.h"
#include "bwselect.h"
#include "CannyAutoThres_X_emxutil.h"
#include "imfill.h"
#include "nullAssignment.h"
#include "round.h"

// Function Definitions

//
// Arguments    : const boolean_T varargin_1[320000]
//                const emxArray_real_T *varargin_2
//                const emxArray_real_T *varargin_3
//                boolean_T varargout_1[320000]
// Return Type  : void
//
void bwselect(const boolean_T varargin_1[320000], const emxArray_real_T
              *varargin_2, const emxArray_real_T *varargin_3, boolean_T
              varargout_1[320000])
{
  emxArray_real_T *r;
  int i1;
  int loop_ub;
  emxArray_real_T *c;
  emxArray_boolean_T *x;
  emxArray_int32_T *ii;
  int nx;
  int idx;
  boolean_T exitg1;
  emxArray_real_T *badPix;
  emxArray_int32_T *b_badPix;
  emxArray_real_T *b_r;
  static boolean_T b_varargin_1[320000];
  emxArray_int32_T *c_badPix;
  emxInit_real_T(&r, 1);
  i1 = r->size[0];
  r->size[0] = varargin_3->size[0];
  emxEnsureCapacity((emxArray__common *)r, i1, sizeof(double));
  loop_ub = varargin_3->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    r->data[i1] = varargin_3->data[i1];
  }

  emxInit_real_T(&c, 1);
  b_round();
  i1 = c->size[0];
  c->size[0] = varargin_2->size[0];
  emxEnsureCapacity((emxArray__common *)c, i1, sizeof(double));
  loop_ub = varargin_2->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    c->data[i1] = varargin_2->data[i1];
  }

  emxInit_boolean_T(&x, 1);
  b_round();
  i1 = x->size[0];
  x->size[0] = r->size[0];
  emxEnsureCapacity((emxArray__common *)x, i1, sizeof(boolean_T));
  loop_ub = r->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    x->data[i1] = ((r->data[i1] < 1.0) || (r->data[i1] > 800.0) || (c->data[i1] <
      1.0) || (c->data[i1] > 400.0));
  }

  emxInit_int32_T(&ii, 1);
  nx = x->size[0];
  idx = 0;
  i1 = ii->size[0];
  ii->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)ii, i1, sizeof(int));
  loop_ub = 1;
  exitg1 = false;
  while ((!exitg1) && (loop_ub <= nx)) {
    if (x->data[loop_ub - 1]) {
      idx++;
      ii->data[idx - 1] = loop_ub;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        loop_ub++;
      }
    } else {
      loop_ub++;
    }
  }

  if (x->size[0] == 1) {
    if (idx == 0) {
      i1 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i1, sizeof(int));
    }
  } else {
    i1 = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)ii, i1, sizeof(int));
  }

  emxFree_boolean_T(&x);
  emxInit_real_T(&badPix, 1);
  i1 = badPix->size[0];
  badPix->size[0] = ii->size[0];
  emxEnsureCapacity((emxArray__common *)badPix, i1, sizeof(double));
  loop_ub = ii->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    badPix->data[i1] = ii->data[i1];
  }

  emxFree_int32_T(&ii);
  if (!(badPix->size[0] == 0)) {
    emxInit_int32_T(&b_badPix, 1);
    i1 = b_badPix->size[0];
    b_badPix->size[0] = badPix->size[0];
    emxEnsureCapacity((emxArray__common *)b_badPix, i1, sizeof(int));
    loop_ub = badPix->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_badPix->data[i1] = (int)badPix->data[i1];
    }

    emxInit_int32_T(&c_badPix, 1);
    nullAssignment(r, b_badPix);
    i1 = c_badPix->size[0];
    c_badPix->size[0] = badPix->size[0];
    emxEnsureCapacity((emxArray__common *)c_badPix, i1, sizeof(int));
    loop_ub = badPix->size[0];
    emxFree_int32_T(&b_badPix);
    for (i1 = 0; i1 < loop_ub; i1++) {
      c_badPix->data[i1] = (int)badPix->data[i1];
    }

    nullAssignment(c, c_badPix);
    emxFree_int32_T(&c_badPix);
  }

  emxFree_real_T(&badPix);
  for (i1 = 0; i1 < 320000; i1++) {
    b_varargin_1[i1] = !varargin_1[i1];
  }

  emxInit_real_T(&b_r, 1);
  i1 = b_r->size[0];
  b_r->size[0] = r->size[0];
  emxEnsureCapacity((emxArray__common *)b_r, i1, sizeof(double));
  loop_ub = r->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_r->data[i1] = (int)r->data[i1] + 800 * ((int)c->data[i1] - 1);
  }

  emxFree_real_T(&c);
  emxFree_real_T(&r);
  imfill(b_varargin_1, b_r, varargout_1);
  emxFree_real_T(&b_r);
  for (i1 = 0; i1 < 320000; i1++) {
    varargout_1[i1] = (varargout_1[i1] && varargin_1[i1]);
  }
}

//
// File trailer for bwselect.cpp
//
// [EOF]
//
