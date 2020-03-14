//
// File: main.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 12-Mar-2020 16:36:47
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
#include "include/main.h"
#include "ImageFill_terminate.h"
#include "ImageFill_initialize.h"

// Function Declarations
static void argInit_800x800_boolean_T(boolean_T result[640000]);

static boolean_T argInit_boolean_T();

static double argInit_real_T();

static void main_ImageFill();

// Function Definitions

//
// Arguments    : boolean_T result[640000]
// Return Type  : void
//
static void argInit_800x800_boolean_T(boolean_T result[640000]) {
    int idx0;
    int idx1;

    // Loop over the array to initialize each element.
    for (idx0 = 0; idx0 < 800; idx0++) {
        for (idx1 = 0; idx1 < 800; idx1++) {
            // Set the value of the array element.
            // Change this value to the value that the application requires.
            result[idx0 + 800 * idx1] = argInit_boolean_T();
        }
    }
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
// Return Type  : void
//
static void main_ImageFill() {
    static boolean_T bv0[640000];
    static boolean_T outputImage[640000];

    // Initialize function 'ImageFill' input arguments.
    // Initialize function input argument 'inputImage'.
    // Call the entry-point 'ImageFill'.
    argInit_800x800_boolean_T(bv0);
    ImageFill(bv0, argInit_real_T(), argInit_real_T(), outputImage);
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
