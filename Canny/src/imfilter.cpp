//
// File: imfilter.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 21-Mar-2020 11:39:34
//

// Include Files
#include "rt_nonfinite.h"
#include "Canny.h"
#include "imfilter.h"
#include "Canny_emxutil.h"

// Function Definitions

//
// Arguments    : emxArray_real32_T *varargin_1
//                const double varargin_2[13]
// Return Type  : void
//
void b_imfilter(emxArray_real32_T *varargin_1, const double varargin_2[13])
{
  double pad[2];
  int i;
  emxArray_real32_T *a;
  float h[13];
  int k;
  double b_pad;
  int iv3[2];
  int lastRowA;
  int aidx;
  boolean_T b1;
  int cidx;
  int cEnd;
  int cEnd1;
  int ma;
  int na;
  int lastColB;
  int lastRowB;
  int j;
  int lastColA;
  int b_j;
  int iC;
  int iA;
  int iB;
  pad[0] = 0.0;
  pad[1] = 6.0;
  if (!((varargin_1->size[0] == 0) || (varargin_1->size[1] == 0))) {
    for (i = 0; i < 13; i++) {
      h[i] = (float)varargin_2[i];
    }

    emxInit_real32_T(&a, 2);
    padImage(varargin_1, pad, a);
    for (k = 0; k < 2; k++) {
      b_pad = ((double)a->size[k] - (1.0 + 12.0 * (double)k)) + 1.0;
      iv3[k] = (int)b_pad;
    }

    i = varargin_1->size[0] * varargin_1->size[1];
    varargin_1->size[0] = iv3[0];
    varargin_1->size[1] = iv3[1];
    emxEnsureCapacity((emxArray__common *)varargin_1, i, sizeof(float));
    lastRowA = iv3[1];
    for (i = 0; i < lastRowA; i++) {
      aidx = iv3[0];
      for (cidx = 0; cidx < aidx; cidx++) {
        varargin_1->data[cidx + varargin_1->size[0] * i] = 0.0F;
      }
    }

    if ((a->size[0] == 0) || ((iv3[0] == 0) || (iv3[1] == 0))) {
      b1 = true;
    } else {
      b1 = false;
    }

    if (!b1) {
      cEnd = a->size[1];
      cEnd1 = a->size[0];
      ma = a->size[0];
      na = a->size[1];
      if (13 <= a->size[1] - 1) {
        lastColB = 13;
      } else {
        lastColB = a->size[1];
      }

      if (1 <= a->size[0] - 1) {
        lastRowB = 1;
      } else {
        lastRowB = a->size[0];
      }

      for (j = 0; j < lastColB; j++) {
        if ((j + na) - 1 < cEnd - 1) {
          lastColA = na;
        } else {
          lastColA = cEnd - j;
        }

        if (j < 12) {
          k = 12 - j;
        } else {
          k = 0;
        }

        while (k <= lastColA - 1) {
          if (j + k > 12) {
            b_j = (j + k) - 12;
          } else {
            b_j = 0;
          }

          iC = b_j * cEnd1;
          iA = k * ma;
          iB = j;
          i = 0;
          while (i <= lastRowB - 1) {
            if (ma <= cEnd1 - 1) {
              lastRowA = ma;
            } else {
              lastRowA = cEnd1;
            }

            aidx = iA;
            cidx = iC;
            for (i = 1; i <= lastRowA; i++) {
              varargin_1->data[cidx] += h[iB] * a->data[aidx];
              aidx++;
              cidx++;
            }

            iB++;
            iC++;
            i = 1;
          }

          k++;
        }
      }
    }

    emxFree_real32_T(&a);
  }
}

//
// Arguments    : emxArray_real32_T *varargin_1
// Return Type  : void
//
void imfilter(emxArray_real32_T *varargin_1)
{
  double pad[2];
  emxArray_real32_T *a;
  int k;
  int j;
  double b_pad;
  int iv2[2];
  int firstRowA;
  int aidx;
  boolean_T b0;
  int cidx;
  int cEnd;
  int cEnd1;
  int ma;
  int na;
  int lastColB;
  int lastRowB;
  int lastColA;
  int iC;
  int iA;
  int iB;
  int i;
  int b_i;
  int a_length;
  static const float B[13] = { 3.48133581E-5F, 0.00054457254F, 0.00516676065F,
    0.0297326539F, 0.103777163F, 0.219696254F, 0.282095581F, 0.219696254F,
    0.103777163F, 0.0297326539F, 0.00516676065F, 0.00054457254F, 3.48133581E-5F
  };

  pad[0] = 6.0;
  pad[1] = 0.0;
  if (!((varargin_1->size[0] == 0) || (varargin_1->size[1] == 0))) {
    emxInit_real32_T(&a, 2);
    padImage(varargin_1, pad, a);
    for (k = 0; k < 2; k++) {
      b_pad = ((double)a->size[k] - (13.0 + -12.0 * (double)k)) + 1.0;
      iv2[k] = (int)b_pad;
    }

    j = varargin_1->size[0] * varargin_1->size[1];
    varargin_1->size[0] = iv2[0];
    varargin_1->size[1] = iv2[1];
    emxEnsureCapacity((emxArray__common *)varargin_1, j, sizeof(float));
    firstRowA = iv2[1];
    for (j = 0; j < firstRowA; j++) {
      aidx = iv2[0];
      for (cidx = 0; cidx < aidx; cidx++) {
        varargin_1->data[cidx + varargin_1->size[0] * j] = 0.0F;
      }
    }

    if ((a->size[1] == 0) || ((iv2[0] == 0) || (iv2[1] == 0))) {
      b0 = true;
    } else {
      b0 = false;
    }

    if (!b0) {
      cEnd = a->size[1];
      cEnd1 = a->size[0];
      ma = a->size[0];
      na = a->size[1];
      if (1 <= a->size[1] - 1) {
        lastColB = 1;
      } else {
        lastColB = a->size[1];
      }

      if (13 <= a->size[0] - 1) {
        lastRowB = 13;
      } else {
        lastRowB = a->size[0];
      }

      j = 0;
      while (j <= lastColB - 1) {
        if (na - 1 < cEnd - 1) {
          lastColA = na;
        } else {
          lastColA = cEnd;
        }

        for (k = 0; k < lastColA; k++) {
          if (k > 0) {
            firstRowA = k;
          } else {
            firstRowA = 0;
          }

          iC = firstRowA * (cEnd1 - 12);
          iA = k * ma;
          iB = 0;
          for (i = 0; i < lastRowB; i++) {
            if (i < 12) {
              firstRowA = 12 - i;
            } else {
              firstRowA = 0;
            }

            if (i + ma <= cEnd1 - 1) {
              b_i = ma;
            } else {
              b_i = cEnd1 - i;
            }

            a_length = b_i - firstRowA;
            aidx = iA + firstRowA;
            cidx = iC;
            for (j = 1; j <= a_length; j++) {
              varargin_1->data[cidx] += B[iB] * a->data[aidx];
              aidx++;
              cidx++;
            }

            iB++;
            if (i >= 12) {
              iC++;
            }
          }
        }

        j = 1;
      }
    }

    emxFree_real32_T(&a);
  }
}

//
// Arguments    : const emxArray_real32_T *a_tmp
//                const double pad[2]
//                emxArray_real32_T *a
// Return Type  : void
//
void padImage(const emxArray_real32_T *a_tmp, const double pad[2],
              emxArray_real32_T *a)
{
  int i0;
  double dv2[2];
  double sizeA[2];
  unsigned int b_sizeA[2];
  int loop_ub;
  double mtmp;
  double varargin_1[2];
  emxArray_int32_T *idxA;
  int onesVector_size_idx_1;
  emxArray_uint32_T *y;
  emxArray_uint32_T *idxDir;
  emxArray_int32_T *r0;
  emxArray_int32_T *b_idxDir;
  emxArray_int32_T *c_idxDir;
  int i;
  if ((a_tmp->size[0] == 0) || (a_tmp->size[1] == 0)) {
    for (i0 = 0; i0 < 2; i0++) {
      sizeA[i0] = (double)a_tmp->size[i0] + 2.0 * pad[i0];
    }

    i0 = a->size[0] * a->size[1];
    a->size[0] = (int)sizeA[0];
    a->size[1] = (int)sizeA[1];
    emxEnsureCapacity((emxArray__common *)a, i0, sizeof(float));
    loop_ub = (int)sizeA[0] * (int)sizeA[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      a->data[i0] = 0.0F;
    }
  } else {
    for (i0 = 0; i0 < 2; i0++) {
      sizeA[i0] = a_tmp->size[i0];
    }

    dv2[0] = 2.0 * pad[0];
    dv2[1] = 2.0 * pad[1];
    b_sizeA[0] = (unsigned int)sizeA[0];
    b_sizeA[1] = (unsigned int)sizeA[1];
    for (i0 = 0; i0 < 2; i0++) {
      varargin_1[i0] = dv2[i0] + (double)b_sizeA[i0];
    }

    mtmp = varargin_1[0];
    if (varargin_1[1] > varargin_1[0]) {
      mtmp = varargin_1[1];
    }

    emxInit_int32_T(&idxA, 2);
    i0 = idxA->size[0] * idxA->size[1];
    idxA->size[0] = (int)mtmp;
    idxA->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)idxA, i0, sizeof(int));
    onesVector_size_idx_1 = (int)pad[0];
    emxInit_uint32_T(&y, 2);
    i0 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)(unsigned int)sizeA[0];
    emxEnsureCapacity((emxArray__common *)y, i0, sizeof(unsigned int));
    loop_ub = (int)((unsigned int)sizeA[0] + MAX_uint32_T);
    for (i0 = 0; i0 <= loop_ub; i0++) {
      y->data[y->size[0] * i0] = 1U + i0;
    }

    emxInit_uint32_T(&idxDir, 2);
    i0 = idxDir->size[0] * idxDir->size[1];
    idxDir->size[0] = 1;
    idxDir->size[1] = ((int)pad[0] + y->size[1]) + (int)pad[0];
    emxEnsureCapacity((emxArray__common *)idxDir, i0, sizeof(unsigned int));
    loop_ub = (int)pad[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
      idxDir->data[idxDir->size[0] * i0] = 1U;
    }

    loop_ub = y->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      idxDir->data[idxDir->size[0] * (i0 + onesVector_size_idx_1)] = y->data
        [y->size[0] * i0];
    }

    loop_ub = (int)pad[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
      idxDir->data[idxDir->size[0] * ((i0 + onesVector_size_idx_1) + y->size[1])]
        = (unsigned int)sizeA[0];
    }

    emxInit_int32_T1(&r0, 1);
    loop_ub = idxDir->size[1];
    i0 = r0->size[0];
    r0->size[0] = loop_ub;
    emxEnsureCapacity((emxArray__common *)r0, i0, sizeof(int));
    for (i0 = 0; i0 < loop_ub; i0++) {
      r0->data[i0] = i0;
    }

    emxInit_int32_T(&b_idxDir, 2);
    i0 = b_idxDir->size[0] * b_idxDir->size[1];
    b_idxDir->size[0] = 1;
    b_idxDir->size[1] = idxDir->size[1];
    emxEnsureCapacity((emxArray__common *)b_idxDir, i0, sizeof(int));
    loop_ub = idxDir->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      b_idxDir->data[b_idxDir->size[0] * i0] = (int)idxDir->data[idxDir->size[0]
        * i0];
    }

    onesVector_size_idx_1 = r0->size[0];
    for (i0 = 0; i0 < onesVector_size_idx_1; i0++) {
      idxA->data[r0->data[i0]] = b_idxDir->data[i0];
    }

    emxFree_int32_T(&b_idxDir);
    onesVector_size_idx_1 = (int)pad[1];
    i0 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)(unsigned int)sizeA[1];
    emxEnsureCapacity((emxArray__common *)y, i0, sizeof(unsigned int));
    loop_ub = (int)((unsigned int)sizeA[1] + MAX_uint32_T);
    for (i0 = 0; i0 <= loop_ub; i0++) {
      y->data[y->size[0] * i0] = 1U + i0;
    }

    i0 = idxDir->size[0] * idxDir->size[1];
    idxDir->size[0] = 1;
    idxDir->size[1] = ((int)pad[1] + y->size[1]) + (int)pad[1];
    emxEnsureCapacity((emxArray__common *)idxDir, i0, sizeof(unsigned int));
    loop_ub = (int)pad[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      idxDir->data[idxDir->size[0] * i0] = 1U;
    }

    loop_ub = y->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      idxDir->data[idxDir->size[0] * (i0 + onesVector_size_idx_1)] = y->data
        [y->size[0] * i0];
    }

    loop_ub = (int)pad[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      idxDir->data[idxDir->size[0] * ((i0 + onesVector_size_idx_1) + y->size[1])]
        = (unsigned int)sizeA[1];
    }

    emxFree_uint32_T(&y);
    loop_ub = idxDir->size[1];
    i0 = r0->size[0];
    r0->size[0] = loop_ub;
    emxEnsureCapacity((emxArray__common *)r0, i0, sizeof(int));
    for (i0 = 0; i0 < loop_ub; i0++) {
      r0->data[i0] = i0;
    }

    emxInit_int32_T(&c_idxDir, 2);
    i0 = c_idxDir->size[0] * c_idxDir->size[1];
    c_idxDir->size[0] = 1;
    c_idxDir->size[1] = idxDir->size[1];
    emxEnsureCapacity((emxArray__common *)c_idxDir, i0, sizeof(int));
    loop_ub = idxDir->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      c_idxDir->data[c_idxDir->size[0] * i0] = (int)idxDir->data[idxDir->size[0]
        * i0];
    }

    emxFree_uint32_T(&idxDir);
    onesVector_size_idx_1 = r0->size[0];
    for (i0 = 0; i0 < onesVector_size_idx_1; i0++) {
      idxA->data[r0->data[i0] + idxA->size[0]] = c_idxDir->data[i0];
    }

    emxFree_int32_T(&c_idxDir);
    emxFree_int32_T(&r0);
    for (i0 = 0; i0 < 2; i0++) {
      sizeA[i0] = (double)a_tmp->size[i0] + 2.0 * pad[i0];
    }

    i0 = a->size[0] * a->size[1];
    a->size[0] = (int)sizeA[0];
    a->size[1] = (int)sizeA[1];
    emxEnsureCapacity((emxArray__common *)a, i0, sizeof(float));
    i0 = a->size[1];
    for (onesVector_size_idx_1 = 0; onesVector_size_idx_1 < i0;
         onesVector_size_idx_1++) {
      loop_ub = a->size[0];
      for (i = 0; i < loop_ub; i++) {
        a->data[i + a->size[0] * onesVector_size_idx_1] = a_tmp->data
          [(idxA->data[i] + a_tmp->size[0] * (idxA->data[onesVector_size_idx_1 +
             idxA->size[0]] - 1)) - 1];
      }
    }

    emxFree_int32_T(&idxA);
  }
}

//
// File trailer for imfilter.cpp
//
// [EOF]
//
