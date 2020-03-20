//
// File: nullAssignment.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 18-Mar-2020 17:37:36
//

// Include Files
#include "rt_nonfinite.h"
#include "CannyAutoThres_X.h"
#include "nullAssignment.h"
#include "CannyAutoThres_X_emxutil.h"

// Function Declarations
static void make_bitarray(int n, const emxArray_int32_T *idx, emxArray_boolean_T
  *b);
static int num_true(const emxArray_boolean_T *b);

// Function Definitions

//
// Arguments    : int n
//                const emxArray_int32_T *idx
//                emxArray_boolean_T *b
// Return Type  : void
//
static void make_bitarray(int n, const emxArray_int32_T *idx, emxArray_boolean_T
  *b)
{
  int k;
  k = b->size[0] * b->size[1];
  b->size[0] = 1;
  b->size[1] = n;
  emxEnsureCapacity((emxArray__common *)b, k, sizeof(boolean_T));
  for (k = 0; k < n; k++) {
    b->data[k] = false;
  }

  for (k = 1; k <= idx->size[0]; k++) {
    b->data[idx->data[k - 1] - 1] = true;
  }
}

//
// Arguments    : const emxArray_boolean_T *b
// Return Type  : int
//
static int num_true(const emxArray_boolean_T *b)
{
  int n;
  int k;
  n = 0;
  for (k = 1; k <= b->size[1]; k++) {
    n += b->data[k - 1];
  }

  return n;
}

//
// Arguments    : emxArray_real_T *x
//                int idx
// Return Type  : void
//
void b_nullAssignment(emxArray_real_T *x, int idx)
{
  int nrowx;
  int i;
  emxArray_real_T *b_x;
  nrowx = x->size[0] - 1;
  for (i = idx; i <= nrowx; i++) {
    x->data[i - 1] = x->data[i];
  }

  if (1 > nrowx) {
    nrowx = 0;
  }

  emxInit_real_T(&b_x, 1);
  i = b_x->size[0];
  b_x->size[0] = nrowx;
  emxEnsureCapacity((emxArray__common *)b_x, i, sizeof(double));
  for (i = 0; i < nrowx; i++) {
    b_x->data[i] = x->data[i];
  }

  i = x->size[0];
  x->size[0] = b_x->size[0];
  emxEnsureCapacity((emxArray__common *)x, i, sizeof(double));
  nrowx = b_x->size[0];
  for (i = 0; i < nrowx; i++) {
    x->data[i] = b_x->data[i];
  }

  emxFree_real_T(&b_x);
}

//
// Arguments    : emxArray_real_T *x
//                const emxArray_int32_T *idx
// Return Type  : void
//
void nullAssignment(emxArray_real_T *x, const emxArray_int32_T *idx)
{
  emxArray_boolean_T *b;
  int nxin;
  int nxout;
  int k0;
  int k;
  emxArray_real_T *b_x;
  emxInit_boolean_T1(&b, 2);
  nxin = x->size[0];
  make_bitarray(x->size[0], idx, b);
  nxout = x->size[0] - num_true(b);
  k0 = -1;
  for (k = 1; k <= nxin; k++) {
    if ((k > b->size[1]) || (!b->data[k - 1])) {
      k0++;
      x->data[k0] = x->data[k - 1];
    }
  }

  emxFree_boolean_T(&b);
  if (1 > nxout) {
    nxin = 0;
  } else {
    nxin = nxout;
  }

  emxInit_real_T(&b_x, 1);
  nxout = b_x->size[0];
  b_x->size[0] = nxin;
  emxEnsureCapacity((emxArray__common *)b_x, nxout, sizeof(double));
  for (nxout = 0; nxout < nxin; nxout++) {
    b_x->data[nxout] = x->data[nxout];
  }

  nxout = x->size[0];
  x->size[0] = b_x->size[0];
  emxEnsureCapacity((emxArray__common *)x, nxout, sizeof(double));
  nxin = b_x->size[0];
  for (nxout = 0; nxout < nxin; nxout++) {
    x->data[nxout] = b_x->data[nxout];
  }

  emxFree_real_T(&b_x);
}

//
// File trailer for nullAssignment.cpp
//
// [EOF]
//
