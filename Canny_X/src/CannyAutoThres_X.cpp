//
// File: CannyAutoThres_X.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 18-Mar-2020 17:37:36
//

// Include Files
#include "rt_nonfinite.h"
#include "CannyAutoThres_X.h"
#include "edge.h"
#include "hypot.h"
#include "imfilter.h"
#include "convn.h"
#include "sum.h"
#include "libmwgetnumcores.h"

// Function Definitions

//
// CANNYAUTOTHRES Summary of this function goes here
//    Detailed explanation goes here
// Arguments    : const float inputImage[320000]
//                boolean_T outputImage[320000]
// Return Type  : void
//
void CannyAutoThres_X(const float inputImage[320000], boolean_T outputImage
                      [320000])
{
  double derivGaussKernel[13];
  static const double dv0[13] = { 0.00050975920363612861, 0.0025659736304223,
    0.014594040963812248, 0.049305200293708981, 0.09498179875488523,
    0.089159205155936727, 0.0, -0.089159205155936727, -0.09498179875488523,
    -0.049305200293708981, -0.014594040963812248, -0.0025659736304223,
    -0.00050975920363612861 };

  int ixstart;
  double out;
  static const double dv1[6] = { 0.0020299751839417141, 0.010218281014351701,
    0.058116735860084041, 0.19634433732941295, 0.37823877042972093,
    0.35505190018248872 };

  static float fv0[324800];
  static const float fv1[13] = { 3.48133581E-5F, 0.00054457254F, 0.00516676065F,
    0.0297326539F, 0.103777163F, 0.219696254F, 0.282095581F, 0.219696254F,
    0.103777163F, 0.0297326539F, 0.00516676065F, 0.00054457254F, 3.48133581E-5F
  };

  static float dx[320000];
  static float magGrad[320000];
  static float fv2[329600];
  static const float fv3[13] = { 3.48133581E-5F, 0.00054457254F, 0.00516676065F,
    0.0297326539F, 0.103777163F, 0.219696254F, 0.282095581F, 0.219696254F,
    0.103777163F, 0.0297326539F, 0.00516676065F, 0.00054457254F, 3.48133581E-5F
  };

  static float dy[320000];
  float idx;
  int ix;
  boolean_T exitg1;
  double counts[64];
  int ii_size_idx_0;
  signed char ii_data[1];
  double highThreshTemp_data[1];
  double highThresh_data[1];
  memcpy(&derivGaussKernel[0], &dv0[0], 13U * sizeof(double));
  for (ixstart = 0; ixstart < 6; ixstart++) {
    derivGaussKernel[ixstart] = dv1[ixstart];
  }

  out = std::abs(sum(*(double (*)[6])&derivGaussKernel[7]));
  for (ixstart = 0; ixstart < 6; ixstart++) {
    derivGaussKernel[7 + ixstart] /= out;
  }

  padImage(inputImage, fv0);
  convn(fv0, fv1, dx);
  memcpy(&magGrad[0], &dx[0], 320000U * sizeof(float));
  imfilter(magGrad, derivGaussKernel, dx);
  b_padImage(inputImage, fv2);
  b_convn(fv2, fv3, dy);
  memcpy(&magGrad[0], &dy[0], 320000U * sizeof(float));
  b_imfilter(magGrad, derivGaussKernel, dy);
  b_hypot(dx, dy, magGrad);
  ixstart = 1;
  idx = magGrad[0];
  if (rtIsNaNF(magGrad[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 320001)) {
      ixstart = ix;
      if (!rtIsNaNF(magGrad[ix - 1])) {
        idx = magGrad[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 320000) {
    while (ixstart + 1 < 320001) {
      if (magGrad[ixstart] > idx) {
        idx = magGrad[ixstart];
      }

      ixstart++;
    }
  }

  if (idx > 0.0F) {
    for (ixstart = 0; ixstart < 320000; ixstart++) {
      magGrad[ixstart] /= idx;
    }
  }

  out = 1.0;
  getnumcores(&out);
  memset(&counts[0], 0, sizeof(double) << 6);
  for (ixstart = 0; ixstart < 320000; ixstart++) {
    if (rtIsNaNF(magGrad[ixstart])) {
      idx = 0.0F;
    } else {
      idx = magGrad[ixstart] * 63.0F + 0.5F;
    }

    if (idx < 0.0F) {
      counts[0]++;
    } else if (idx > 63.0F) {
      counts[63]++;
    } else if (rtIsInfF(magGrad[ixstart])) {
      counts[63]++;
    } else {
      counts[(int)idx]++;
    }
  }

  for (ixstart = 0; ixstart < 63; ixstart++) {
    counts[ixstart + 1] += counts[ixstart];
  }

  ixstart = 0;
  ii_size_idx_0 = 1;
  ix = 1;
  exitg1 = false;
  while ((!exitg1) && (ix < 65)) {
    if (counts[ix - 1] > 224000.0) {
      ixstart = 1;
      ii_data[0] = (signed char)ix;
      exitg1 = true;
    } else {
      ix++;
    }
  }

  if (ixstart == 0) {
    ii_size_idx_0 = 0;
  }

  for (ixstart = 0; ixstart < ii_size_idx_0; ixstart++) {
    highThreshTemp_data[ixstart] = (double)ii_data[ixstart] / 64.0;
  }

  if (ii_size_idx_0 != 0) {
    highThresh_data[0] = highThreshTemp_data[0];
    highThreshTemp_data[0] *= 0.4;
  }

  thinAndThreshold(dx, dy, magGrad, highThreshTemp_data, highThresh_data,
                   outputImage);
}

//
// File trailer for CannyAutoThres_X.cpp
//
// [EOF]
//
