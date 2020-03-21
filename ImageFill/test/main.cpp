//
// File: main.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 21-Mar-2020 11:42:13
//

//***********************************************************************
// This automatically generated example C main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************
// Include Files
#include "rt_nonfinite.h"
#include "ImageFill.h"
#include "main.h"
#include "ImageFill_terminate.h"
#include "ImageFill_emxAPI.h"
#include "ImageFill_initialize.h"

// Function Declarations
static emxArray_real_T *argInit_Unboundedx1_real_T();

static boolean_T argInit_boolean_T();

static double argInit_real_T();

static emxArray_boolean_T *c_argInit_UnboundedxUnbounded_b();

static void main_ImageFill();

// Function Definitions

//
// Arguments    : void
// Return Type  : emxArray_real_T *
//
static emxArray_real_T *argInit_Unboundedx1_real_T() {
    emxArray_real_T *result;
    static int iv1[1] = {2};

    int idx0;

    // Set the size of the array.
    // Change this size to the value that the application requires.
    result = emxCreateND_real_T(1, *(int (*)[1]) &iv1[0]);

    // Loop over the array to initialize each element.
    for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        result->data[idx0] = argInit_real_T();
    }

    return result;
}

//
// Arguments    : void
// Return Type  : boolean_T
//
static boolean_T argInit_boolean_T() {
    return false;
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T() {
    return 0.0;
}

//
// Arguments    : void
// Return Type  : emxArray_boolean_T *
//
static emxArray_boolean_T *c_argInit_UnboundedxUnbounded_b() {
    emxArray_boolean_T *result;
    static int iv0[2] = {2, 2};

    int idx0;
    int idx1;

    // Set the size of the array.
    // Change this size to the value that the application requires.
    result = emxCreateND_boolean_T(2, *(int (*)[2]) &iv0[0]);

    // Loop over the array to initialize each element.
    for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
        for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
            // Set the value of the array element.
            // Change this value to the value that the application requires.
            result->data[idx0 + result->size[0] * idx1] = argInit_boolean_T();
        }
    }

    return result;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_ImageFill() {
    emxArray_boolean_T *outputImage;
    emxArray_boolean_T *inputImage;
    emxArray_real_T *pointIDs;
    emxInitArray_boolean_T(&outputImage, 2);

    // Initialize function 'ImageFill' input arguments.
    // Initialize function input argument 'inputImage'.
    inputImage = c_argInit_UnboundedxUnbounded_b();

    // Initialize function input argument 'pointIDs'.
    pointIDs = argInit_Unboundedx1_real_T();

    // Call the entry-point 'ImageFill'.
    ImageFill(inputImage, pointIDs, outputImage);
    emxDestroyArray_boolean_T(outputImage);
    emxDestroyArray_real_T(pointIDs);
    emxDestroyArray_boolean_T(inputImage);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int, const char *const[]) {
    // Initialize the application.
    // You do not need to do this more than one time.
    ImageFill_initialize();

    // Invoke the entry-point functions.
    // You can call entry-point functions multiple times.
    main_ImageFill();

    // Terminate the application.
    // You do not need to do this more than one time.
    ImageFill_terminate();
    return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
