// Include Files
#include "rt_nonfinite.h"
#include "CannyAutoThres.h"
#include "C_imfill.h"
#include "CannyAutoThres_emxutil.h"
#include "nullAssignment.h"
#include "any1.h"
#include "libmwippreconstruct.h"

// Function Declarations
static void checkLocations(const emxArray_real_T *locations, emxArray_real_T
*locationsVar);

static void checkLocations(const emxArray_real_T *locations, emxArray_real_T
*locationsVar) {
    int i3;
    emxArray_boolean_T *badPixels;
    int loop_ub;
    int s;
    i3 = locationsVar->size[0];
    locationsVar->size[0] = 0;
    emxEnsureCapacity((emxArray__common *) locationsVar, i3, sizeof(double));
    if (!(locations->size[0] == 0)) {
        i3 = locationsVar->size[0];
        locationsVar->size[0] = locations->size[0];
        emxEnsureCapacity((emxArray__common *) locationsVar, i3, sizeof(double));
        loop_ub = locations->size[0];
        for (i3 = 0; i3 < loop_ub; i3++) {
            locationsVar->data[i3] = locations->data[i3];
        }
    }

    emxInit_boolean_T(&badPixels, 1);
    i3 = badPixels->size[0];
    badPixels->size[0] = locations->size[0];
    emxEnsureCapacity((emxArray__common *) badPixels, i3, sizeof(boolean_T));
    loop_ub = locations->size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
        badPixels->data[i3] = ((locations->data[i3] < 1.0) || (locations->data[i3] >
                                                               640000.0));
    }

    if (any(badPixels)) {
        i3 = (int) ((1.0 + (-1.0 - (double) badPixels->size[0])) / -1.0);
        for (loop_ub = 0; loop_ub < i3; loop_ub++) {
            s = badPixels->size[0] - loop_ub;
            if (badPixels->data[s - 1]) {
                b_nullAssignment(locationsVar, s);
            }
        }
    }

    emxFree_boolean_T(&badPixels);
}

void imfill(const boolean_T varargin_1[640000], const emxArray_real_T
*varargin_2, boolean_T I2[640000]) {
    emxArray_real_T *locationsVar;
    int i2;
    int loop_ub;
    static boolean_T mask[640000];
    double imSize[2];
    emxInit_real_T(&locationsVar, 1);
    checkLocations(varargin_2, locationsVar);
    for (i2 = 0; i2 < 640000; i2++) {
        mask[i2] = !varargin_1[i2];
        I2[i2] = false;
    }

    loop_ub = locationsVar->size[0];
    for (i2 = 0; i2 < loop_ub; i2++) {
        I2[(int) locationsVar->data[i2] - 1] = mask[(int) locationsVar->data[i2] - 1];
    }

    emxFree_real_T(&locationsVar);
    for (i2 = 0; i2 < 2; i2++) {
        imSize[i2] = 800.0;
    }

    ippreconstruct_uint8(I2, mask, imSize, 2.0);
    for (i2 = 0; i2 < 640000; i2++) {
        I2[i2] = (varargin_1[i2] || I2[i2]);
    }
}

