//
// File: hypot.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 18-Mar-2020 17:37:36
//

// Include Files
#include "rt_nonfinite.h"
#include "CannyAutoThres_X.h"
#include "hypot.h"

// Function Declarations
static float rt_hypotf_snf(float u0, float u1);

// Function Definitions

//
// Arguments    : float u0
//                float u1
// Return Type  : float
//
static float rt_hypotf_snf(float u0, float u1)
{
  float y;
  float a;
  float b;
  a = std::abs(u0);
  b = std::abs(u1);
  if (a < b) {
    a /= b;
    y = b * std::sqrt(a * a + 1.0F);
  } else if (a > b) {
    b /= a;
    y = a * std::sqrt(b * b + 1.0F);
  } else if (rtIsNaNF(b)) {
    y = b;
  } else {
    y = a * 1.41421354F;
  }

  return y;
}

//
// Arguments    : const float x[320000]
//                const float y[320000]
//                float r[320000]
// Return Type  : void
//
void b_hypot(const float x[320000], const float y[320000], float r[320000])
{
  int k;
  for (k = 0; k < 320000; k++) {
    r[k] = rt_hypotf_snf(x[k], y[k]);
  }
}

//
// File trailer for hypot.cpp
//
// [EOF]
//
