//
// File: sum.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 18-Mar-2020 17:37:36
//

// Include Files
#include "rt_nonfinite.h"
#include "CannyAutoThres_X.h"
#include "sum.h"

// Function Definitions

//
// Arguments    : const double x[6]
// Return Type  : double
//
double sum(const double x[6])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 5; k++) {
    y += x[k + 1];
  }

  return y;
}

//
// File trailer for sum.cpp
//
// [EOF]
//
