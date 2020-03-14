//
// File: ImageFill.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 12-Mar-2020 16:36:47
//

// Include Files
#include "rt_nonfinite.h"
#include "ImageFill.h"
#include "IF_imfill.h"
#include "libmwippreconstruct.h"

// Function Definitions

//
// CANNYAUTOTHRES Summary of this function goes here
//    Detailed explanation goes here
// Arguments    : const boolean_T inputImage[640000]
//                double pointID1
//                double pointID2
//                boolean_T outputImage[640000]
// Return Type  : void
//
void ImageFill(const boolean_T inputImage[640000], double pointID1, double
pointID2, boolean_T outputImage[640000]) {
    double b_pointID1[2];
    double locationsVar_data[2];
    int locationsVar_size[1];
    int i0;
    int loop_ub;
    static boolean_T mask[640000];
    b_pointID1[0] = pointID1;
    b_pointID1[1] = pointID2;
    checkLocations(b_pointID1, locationsVar_data, locationsVar_size);
    for (i0 = 0; i0 < 640000; i0++) {
        mask[i0] = !inputImage[i0];
        outputImage[i0] = false;
    }

    loop_ub = locationsVar_size[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
        outputImage[(int) locationsVar_data[i0] - 1] = mask[(int) locationsVar_data[i0]
                                                            - 1];
    }

    for (i0 = 0; i0 < 2; i0++) {
        b_pointID1[i0] = 800.0;
    }

    ippreconstruct_uint8(outputImage, mask, b_pointID1, 1.0);
    for (i0 = 0; i0 < 640000; i0++) {
        outputImage[i0] = (inputImage[i0] || outputImage[i0]);
    }
}

//
// File trailer for ImageFill.cpp
//
// [EOF]
//
