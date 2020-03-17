//
// File: imfill.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 17-Mar-2020 16:18:51
//

// Include Files
#include "rt_nonfinite.h"
#include "ImageFillOnlyOnePoint.h"
#include "IFO_imfill.h"

// Function Definitions

//
// Arguments    : double locations
//                double locationsVar_data[]
//                int locationsVar_size[1]
// Return Type  : void
//
void checkLocations(double locations, double locationsVar_data[], int
locationsVar_size[1]) {
    boolean_T badPixels;
    locationsVar_size[0] = 1;
    locationsVar_data[0] = locations;
    badPixels = ((locations < 1.0) || (locations > 640000.0));
    if (badPixels) {
        locationsVar_size[0] = 0;
    }
}

//
// File trailer for imfill.cpp
//
// [EOF]
//
