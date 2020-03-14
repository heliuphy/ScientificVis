//
// File: imfill.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 12-Mar-2020 16:36:47
//

// Include Files
#include "rt_nonfinite.h"
#include "ImageFill.h"
#include "imfill.h"

// Function Definitions

//
// Arguments    : const double locations[2]
//                double locationsVar_data[]
//                int locationsVar_size[1]
// Return Type  : void
//
void checkLocations(const double locations[2], double locationsVar_data[], int
locationsVar_size[1]) {
    int i;
    boolean_T y;
    boolean_T badPixels[2];
    boolean_T exitg1;
    int s;
    int i1;
    double b_locationsVar_data[2];
    locationsVar_size[0] = 2;
    for (i = 0; i < 2; i++) {
        locationsVar_data[i] = locations[i];
        badPixels[i] = ((locations[i] < 1.0) || (locations[i] > 640000.0));
    }

    y = false;
    i = 0;
    exitg1 = false;
    while ((!exitg1) && (i < 2)) {
        if (badPixels[i]) {
            y = true;
            exitg1 = true;
        } else {
            i++;
        }
    }

    if (y) {
        for (s = 0; s < 2; s++) {
            if (badPixels[1 - s]) {
                i = 2 - s;
                while (i <= locationsVar_size[0] - 1) {
                    locationsVar_data[0] = locationsVar_data[1];
                    i = 2;
                }

                if (1 > locationsVar_size[0] - 1) {
                    i = -1;
                } else {
                    i = 0;
                }

                for (i1 = 0; i1 <= i; i1++) {
                    b_locationsVar_data[i1] = locationsVar_data[i1];
                }

                locationsVar_size[0] = i + 1;
                i++;
                for (i1 = 0; i1 < i; i1++) {
                    locationsVar_data[i1] = b_locationsVar_data[i1];
                }
            }
        }
    }
}

//
// File trailer for imfill.cpp
//
// [EOF]
//
