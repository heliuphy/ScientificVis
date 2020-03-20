//
// File: edge.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 18-Mar-2020 17:37:36
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
// Arguments    : const float dx[320000]
//                const float dy[320000]
//                const float magGrad[320000]
//                const double lowThresh_data[]
//                const double highThresh_data[]
//                boolean_T H[320000]
// Return Type  : void
//
void thinAndThreshold(const float dx[320000], const float dy[320000], const
                      float magGrad[320000], const double lowThresh_data[],
                      const double highThresh_data[], boolean_T H[320000])
{
  int jj;
  static boolean_T E[320000];
  double sz[2];
  emxArray_int32_T *ii;
  static boolean_T bv0[320000];
  emxArray_int32_T *b_jj;
  int idx;
  int b_ii;
  boolean_T exitg1;
  boolean_T guard1 = false;
  emxArray_real_T *idxStrongC;
  emxArray_real_T *c_ii;
  for (jj = 0; jj < 2; jj++) {
    sz[jj] = 800.0 + -400.0 * (double)jj;
  }

  memset(&E[0], 0, 320000U * sizeof(boolean_T));
  cannythresholding_real32_tbb(dx, dy, magGrad, sz, lowThresh_data[0], E);
  for (jj = 0; jj < 320000; jj++) {
    bv0[jj] = (magGrad[jj] > highThresh_data[0]);
  }

  emxInit_int32_T(&ii, 1);
  emxInit_int32_T(&b_jj, 1);
  idx = 0;
  jj = ii->size[0];
  ii->size[0] = 320000;
  emxEnsureCapacity((emxArray__common *)ii, jj, sizeof(int));
  jj = b_jj->size[0];
  b_jj->size[0] = 320000;
  emxEnsureCapacity((emxArray__common *)b_jj, jj, sizeof(int));
  b_ii = 0;
  jj = 0;
  exitg1 = false;
  while ((!exitg1) && (jj + 1 <= 400)) {
    guard1 = false;
    if (bv0[b_ii + 800 * jj] && E[b_ii + 800 * jj]) {
      idx++;
      ii->data[idx - 1] = b_ii + 1;
      b_jj->data[idx - 1] = jj + 1;
      if (idx >= 320000) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      b_ii++;
      if (b_ii + 1 > 800) {
        b_ii = 0;
        jj++;
      }
    }
  }

  jj = ii->size[0];
  if (1 > idx) {
    ii->size[0] = 0;
  } else {
    ii->size[0] = idx;
  }

  emxEnsureCapacity((emxArray__common *)ii, jj, sizeof(int));
  emxInit_real_T(&idxStrongC, 1);
  jj = b_jj->size[0];
  if (1 > idx) {
    b_jj->size[0] = 0;
  } else {
    b_jj->size[0] = idx;
  }

  emxEnsureCapacity((emxArray__common *)b_jj, jj, sizeof(int));
  jj = idxStrongC->size[0];
  idxStrongC->size[0] = b_jj->size[0];
  emxEnsureCapacity((emxArray__common *)idxStrongC, jj, sizeof(double));
  b_ii = b_jj->size[0];
  for (jj = 0; jj < b_ii; jj++) {
    idxStrongC->data[jj] = b_jj->data[jj];
  }

  emxFree_int32_T(&b_jj);
  if (!(idxStrongC->size[0] == 0)) {
    emxInit_real_T(&c_ii, 1);
    jj = c_ii->size[0];
    c_ii->size[0] = ii->size[0];
    emxEnsureCapacity((emxArray__common *)c_ii, jj, sizeof(double));
    b_ii = ii->size[0];
    for (jj = 0; jj < b_ii; jj++) {
      c_ii->data[jj] = ii->data[jj];
    }

    bwselect(E, idxStrongC, c_ii, H);
    emxFree_real_T(&c_ii);
  } else {
    memset(&H[0], 0, 320000U * sizeof(boolean_T));
  }

  emxFree_int32_T(&ii);
  emxFree_real_T(&idxStrongC);
}

//
// File trailer for edge.cpp
//
// [EOF]
//
