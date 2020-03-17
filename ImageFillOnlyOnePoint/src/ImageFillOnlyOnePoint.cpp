//
// File: ImageFillOnlyOnePoint.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 17-Mar-2020 16:18:51
//

// Include Files
#include "rt_nonfinite.h"
#include "ImageFillOnlyOnePoint.h"
#include "IFO_imfill.h"
#include "libmwippreconstruct.h"

// Function Definitions

//
// CANNYAUTOTHRES Summary of this function goes here
//    Detailed explanation goes here
// Arguments    : const boolean_T inputImage[640000]
//                double pointID1
//                boolean_T outputImage[640000]
// Return Type  : void
//
void ImageFillOnlyOnePoint(const boolean_T inputImage[640000], double pointID1,
                           boolean_T outputImage[640000]) {
    double locationsVar_data[1];
    int locationsVar_size[1];
    int i0;
    int loop_ub;
    static boolean_T mask[640000];
    double imSize[2];
    checkLocations(pointID1, locationsVar_data, locationsVar_size);
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
        imSize[i0] = 800.0;
    }

    ippreconstruct_uint8(outputImage, mask, imSize, 1.0);
    for (i0 = 0; i0 < 640000; i0++) {
        outputImage[i0] = (inputImage[i0] || outputImage[i0]);
    }
}

//
// File trailer for ImageFillOnlyOnePoint.cpp
//
// [EOF]
//
