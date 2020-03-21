//
// File: ImageFill.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 21-Mar-2020 11:42:13
//

// Include Files
#include "rt_nonfinite.h"
#include "ImageFill.h"
#include "ImageFill_emxutil.h"
#include "libmwippreconstruct.h"

// Function Definitions

//
// CANNYAUTOTHRES Summary of this function goes here
//    Detailed explanation goes here
// Arguments    : const emxArray_boolean_T *inputImage
//                const emxArray_real_T *pointIDs
//                emxArray_boolean_T *outputImage
// Return Type  : void
//
void ImageFill(const emxArray_boolean_T *inputImage, const emxArray_real_T
               *pointIDs, emxArray_boolean_T *outputImage)
{
  int i0;
  int loop_ub;
  emxArray_real_T *locationsVar;
  double image_size[2];
  emxArray_boolean_T *badPixels;
  double y;
  boolean_T b_y;
  boolean_T exitg1;
  boolean_T b0;
  int s;
  emxArray_real_T *b_locationsVar;
  emxArray_boolean_T *mask;
  int nrowx;
  i0 = outputImage->size[0] * outputImage->size[1];
  outputImage->size[0] = inputImage->size[0];
  outputImage->size[1] = inputImage->size[1];
  emxEnsureCapacity((emxArray__common *)outputImage, i0, sizeof(boolean_T));
  loop_ub = inputImage->size[0] * inputImage->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    outputImage->data[i0] = inputImage->data[i0];
  }

  for (i0 = 0; i0 < 2; i0++) {
    image_size[i0] = inputImage->size[i0];
  }

  emxInit_real_T(&locationsVar, 1);
  i0 = locationsVar->size[0];
  locationsVar->size[0] = 0;
  emxEnsureCapacity((emxArray__common *)locationsVar, i0, sizeof(double));
  if (!(pointIDs->size[0] == 0)) {
    i0 = locationsVar->size[0];
    locationsVar->size[0] = pointIDs->size[0];
    emxEnsureCapacity((emxArray__common *)locationsVar, i0, sizeof(double));
    loop_ub = pointIDs->size[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
      locationsVar->data[i0] = pointIDs->data[i0];
    }
  }

  emxInit_boolean_T1(&badPixels, 1);
  y = (double)(unsigned int)image_size[0] * (double)(unsigned int)image_size[1];
  i0 = badPixels->size[0];
  badPixels->size[0] = pointIDs->size[0];
  emxEnsureCapacity((emxArray__common *)badPixels, i0, sizeof(boolean_T));
  loop_ub = pointIDs->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    badPixels->data[i0] = ((pointIDs->data[i0] < 1.0) || (pointIDs->data[i0] > y));
  }

  b_y = false;
  loop_ub = 1;
  exitg1 = false;
  while ((!exitg1) && (loop_ub <= badPixels->size[0])) {
    b0 = !badPixels->data[loop_ub - 1];
    if (!b0) {
      b_y = true;
      exitg1 = true;
    } else {
      loop_ub++;
    }
  }

  if (b_y) {
    i0 = (int)((1.0 + (-1.0 - (double)badPixels->size[0])) / -1.0);
    s = 0;
    emxInit_real_T(&b_locationsVar, 1);
    while (s <= i0 - 1) {
      loop_ub = badPixels->size[0] - s;
      if (badPixels->data[loop_ub - 1]) {
        nrowx = locationsVar->size[0] - 1;
        while (loop_ub <= nrowx) {
          locationsVar->data[loop_ub - 1] = locationsVar->data[loop_ub];
          loop_ub++;
        }

        if (1 > nrowx) {
          loop_ub = 0;
        } else {
          loop_ub = nrowx;
        }

        nrowx = b_locationsVar->size[0];
        b_locationsVar->size[0] = loop_ub;
        emxEnsureCapacity((emxArray__common *)b_locationsVar, nrowx, sizeof
                          (double));
        for (nrowx = 0; nrowx < loop_ub; nrowx++) {
          b_locationsVar->data[nrowx] = locationsVar->data[nrowx];
        }

        nrowx = locationsVar->size[0];
        locationsVar->size[0] = b_locationsVar->size[0];
        emxEnsureCapacity((emxArray__common *)locationsVar, nrowx, sizeof(double));
        loop_ub = b_locationsVar->size[0];
        for (nrowx = 0; nrowx < loop_ub; nrowx++) {
          locationsVar->data[nrowx] = b_locationsVar->data[nrowx];
        }
      }

      s++;
    }

    emxFree_real_T(&b_locationsVar);
  }

  emxFree_boolean_T(&badPixels);
  if (!((inputImage->size[0] == 0) || (inputImage->size[1] == 0))) {
    emxInit_boolean_T(&mask, 2);
    i0 = mask->size[0] * mask->size[1];
    mask->size[0] = inputImage->size[0];
    mask->size[1] = inputImage->size[1];
    emxEnsureCapacity((emxArray__common *)mask, i0, sizeof(boolean_T));
    loop_ub = inputImage->size[0] * inputImage->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      mask->data[i0] = !inputImage->data[i0];
    }

    i0 = outputImage->size[0] * outputImage->size[1];
    outputImage->size[0] = mask->size[0];
    outputImage->size[1] = mask->size[1];
    emxEnsureCapacity((emxArray__common *)outputImage, i0, sizeof(boolean_T));
    loop_ub = mask->size[0] * mask->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      outputImage->data[i0] = false;
    }

    loop_ub = locationsVar->size[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
      outputImage->data[(int)locationsVar->data[i0] - 1] = mask->data[(int)
        locationsVar->data[i0] - 1];
    }

    for (i0 = 0; i0 < 2; i0++) {
      image_size[i0] = outputImage->size[i0];
    }

    ippreconstruct_uint8(&outputImage->data[0], &mask->data[0], image_size, 1.0);
    i0 = outputImage->size[0] * outputImage->size[1];
    outputImage->size[0] = inputImage->size[0];
    outputImage->size[1] = inputImage->size[1];
    emxEnsureCapacity((emxArray__common *)outputImage, i0, sizeof(boolean_T));
    loop_ub = inputImage->size[0] * inputImage->size[1];
    emxFree_boolean_T(&mask);
    for (i0 = 0; i0 < loop_ub; i0++) {
      outputImage->data[i0] = (inputImage->data[i0] || outputImage->data[i0]);
    }
  }

  emxFree_real_T(&locationsVar);
}

//
// File trailer for ImageFill.cpp
//
// [EOF]
//
