// Include Files
#include "rt_nonfinite.h"
#include "ImageFill_X.h"
#include "main.h"
#include "ImageFill_X_terminate.h"
#include "ImageFill_X_initialize.h"

// Function Declarations
static void argInit_456x568_boolean_T(boolean_T result[259008]);
static boolean_T argInit_boolean_T();
static double argInit_real_T();
static void main_ImageFill_X();

// Function Definitions

//
// Arguments    : boolean_T result[259008]
// Return Type  : void
//
static void argInit_456x568_boolean_T(boolean_T result[259008])
{
  int idx0;
  int idx1;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 456; idx0++) {
    for (idx1 = 0; idx1 < 568; idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result[idx0 + 456 * idx1] = argInit_boolean_T();
    }
  }
}

//
// Arguments    : void
// Return Type  : boolean_T
//
static boolean_T argInit_boolean_T()
{
  return false;
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_ImageFill_X()
{
  static boolean_T bv0[259008];
  static boolean_T outputImage[259008];

  // Initialize function 'ImageFill_X' input arguments.
  // Initialize function input argument 'inputImage'.
  // Call the entry-point 'ImageFill_X'.
  argInit_456x568_boolean_T(bv0);
  ImageFill_X(bv0, argInit_real_T(), argInit_real_T(), outputImage);
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
  ImageFill_X_initialize();

  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_ImageFill_X();

  // Terminate the application.
  // You do not need to do this more than one time.
  ImageFill_X_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
