//
// File: main.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 18-Mar-2020 17:37:36
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
#include "CannyAutoThres_X.h"
#include "main.h"
#include "CannyAutoThres_X_terminate.h"
#include "CannyAutoThres_X_initialize.h"

// Function Declarations
static void argInit_800x400_real32_T(float result[320000]);
static float argInit_real32_T();
static void main_CannyAutoThres_X();

// Function Definitions

//
// Arguments    : float result[320000]
// Return Type  : void
//
static void argInit_800x400_real32_T(float result[320000])
{
  int idx0;
  int idx1;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 800; idx0++) {
    for (idx1 = 0; idx1 < 400; idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result[idx0 + 800 * idx1] = argInit_real32_T();
    }
  }
}

//
// Arguments    : void
// Return Type  : float
//
static float argInit_real32_T()
{
  return 0.0F;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_CannyAutoThres_X()
{
  static float fv6[320000];
  static boolean_T outputImage[320000];

  // Initialize function 'CannyAutoThres_X' input arguments.
  // Initialize function input argument 'inputImage'.
  // Call the entry-point 'CannyAutoThres_X'.
  argInit_800x400_real32_T(fv6);
  CannyAutoThres_X(fv6, outputImage);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int, const char * const [])
{
  // Initialize the application.
  // You do not need to do this more than one time.
  CannyAutoThres_X_initialize();

  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_CannyAutoThres_X();

  // Terminate the application.
  // You do not need to do this more than one time.
  CannyAutoThres_X_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
