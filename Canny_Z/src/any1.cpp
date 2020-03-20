//
// File: any1.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 12-Mar-2020 09:21:19
//

// Include Files
#include "rt_nonfinite.h"
#include "CannyAutoThres.h"
#include "any1.h"

// Function Definitions

//
// Arguments    : const emxArray_boolean_T *x
// Return Type  : boolean_T
//
boolean_T any(const emxArray_boolean_T *x) {
    boolean_T y;
    int ix;
    boolean_T exitg1;
    boolean_T b0;
    y = false;
    ix = 1;
    exitg1 = false;
    while ((!exitg1) && (ix <= x->size[0])) {
        b0 = !x->data[ix - 1];
        if (!b0) {
            y = true;
            exitg1 = true;
        } else {
            ix++;
        }
    }

    return y;
}

//
// File trailer for any1.cpp
//
// [EOF]
//
