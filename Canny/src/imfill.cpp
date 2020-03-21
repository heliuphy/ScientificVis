//
// File: imfill.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 21-Mar-2020 11:39:34
//

// Include Files
#include "rt_nonfinite.h"
#include "Canny.h"
#include "imfill.h"
#include "Canny_emxutil.h"
#include "libmwippreconstruct.h"

// Function Definitions

//
// Arguments    : emxArray_boolean_T *varargin_1
//                const emxArray_real_T *varargin_2
// Return Type  : void
//
void imfill(emxArray_boolean_T *varargin_1, const emxArray_real_T *varargin_2) {
    int i2;
    emxArray_real_T *locationsVar;
    double image_size[2];
    emxArray_boolean_T *badPixels;
    double y;
    int nrowx;
    boolean_T b_y;
    int ix;
    boolean_T exitg1;
    boolean_T b2;
    int s;
    emxArray_real_T *b_locationsVar;
    emxArray_boolean_T *mask;
    emxArray_boolean_T *marker;
    int i3;
    for (i2 = 0; i2 < 2; i2++) {
        image_size[i2] = varargin_1->size[i2];
    }

    emxInit_real_T(&locationsVar, 1);
    i2 = locationsVar->size[0];
    locationsVar->size[0] = 0;
    emxEnsureCapacity((emxArray__common *) locationsVar, i2, sizeof(double));
    if (!(varargin_2->size[0] == 0)) {
        i2 = locationsVar->size[0];
        locationsVar->size[0] = varargin_2->size[0];
        emxEnsureCapacity((emxArray__common *) locationsVar, i2, sizeof(double));
        nrowx = varargin_2->size[0];
        for (i2 = 0; i2 < nrowx; i2++) {
            locationsVar->data[i2] = varargin_2->data[i2];
        }
    }

    emxInit_boolean_T1(&badPixels, 1);
    y = image_size[0] * image_size[1];
    i2 = badPixels->size[0];
    badPixels->size[0] = varargin_2->size[0];
    emxEnsureCapacity((emxArray__common *) badPixels, i2, sizeof(boolean_T));
    nrowx = varargin_2->size[0];
    for (i2 = 0; i2 < nrowx; i2++) {
        badPixels->data[i2] = ((varargin_2->data[i2] < 1.0) || (varargin_2->data[i2]
                                                                > y));
    }

    b_y = false;
    ix = 1;
    exitg1 = false;
    while ((!exitg1) && (ix <= badPixels->size[0])) {
        b2 = !badPixels->data[ix - 1];
        if (!b2) {
            b_y = true;
            exitg1 = true;
        } else {
            ix++;
        }
    }

    if (b_y) {
        i2 = (int) ((1.0 + (-1.0 - (double) badPixels->size[0])) / -1.0);
        s = 0;
        emxInit_real_T(&b_locationsVar, 1);
        while (s <= i2 - 1) {
            ix = badPixels->size[0] - s;
            if (badPixels->data[ix - 1]) {
                nrowx = locationsVar->size[0] - 1;
                while (ix <= nrowx) {
                    locationsVar->data[ix - 1] = locationsVar->data[ix];
                    ix++;
                }

                if (1 > nrowx) {
                    nrowx = 0;
                }

                i3 = b_locationsVar->size[0];
                b_locationsVar->size[0] = nrowx;
                emxEnsureCapacity((emxArray__common *) b_locationsVar, i3, sizeof(double));
                for (i3 = 0; i3 < nrowx; i3++) {
                    b_locationsVar->data[i3] = locationsVar->data[i3];
                }

                i3 = locationsVar->size[0];
                locationsVar->size[0] = b_locationsVar->size[0];
                emxEnsureCapacity((emxArray__common *) locationsVar, i3, sizeof(double));
                nrowx = b_locationsVar->size[0];
                for (i3 = 0; i3 < nrowx; i3++) {
                    locationsVar->data[i3] = b_locationsVar->data[i3];
                }
            }

            s++;
        }

        emxFree_real_T(&b_locationsVar);
    }

    emxFree_boolean_T(&badPixels);
    if (!((varargin_1->size[0] == 0) || (varargin_1->size[1] == 0))) {
        emxInit_boolean_T(&mask, 2);
        i2 = mask->size[0] * mask->size[1];
        mask->size[0] = varargin_1->size[0];
        mask->size[1] = varargin_1->size[1];
        emxEnsureCapacity((emxArray__common *) mask, i2, sizeof(boolean_T));
        nrowx = varargin_1->size[0] * varargin_1->size[1];
        for (i2 = 0; i2 < nrowx; i2++) {
            mask->data[i2] = !varargin_1->data[i2];
        }

        emxInit_boolean_T(&marker, 2);
        i2 = marker->size[0] * marker->size[1];
        marker->size[0] = mask->size[0];
        marker->size[1] = mask->size[1];
        emxEnsureCapacity((emxArray__common *) marker, i2, sizeof(boolean_T));
        nrowx = mask->size[0] * mask->size[1];
        for (i2 = 0; i2 < nrowx; i2++) {
            marker->data[i2] = false;
        }

        nrowx = locationsVar->size[0];
        for (i2 = 0; i2 < nrowx; i2++) {
            marker->data[(int) locationsVar->data[i2] - 1] = mask->data[(int)
                                                                                locationsVar->data[i2] - 1];
        }

        for (i2 = 0; i2 < 2; i2++) {
            image_size[i2] = marker->size[i2];
        }

        ippreconstruct_uint8(&marker->data[0], &mask->data[0], image_size, 2.0);
        i2 = varargin_1->size[0] * varargin_1->size[1];
        emxEnsureCapacity((emxArray__common *) varargin_1, i2, sizeof(boolean_T));
        nrowx = varargin_1->size[1];
        emxFree_boolean_T(&mask);
        for (i2 = 0; i2 < nrowx; i2++) {
            ix = varargin_1->size[0];
            for (i3 = 0; i3 < ix; i3++) {
                varargin_1->data[i3 + varargin_1->size[0] * i2] = (varargin_1->data[i3 +
                                                                                    varargin_1->size[0] * i2] ||
                                                                   marker->data[i3 + marker->size[0] * i2]);
            }
        }

        emxFree_boolean_T(&marker);
    }

    emxFree_real_T(&locationsVar);
}

//
// File trailer for imfill.cpp
//
// [EOF]
//
