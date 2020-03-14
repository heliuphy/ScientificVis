// Include Files
#include "rt_nonfinite.h"
#include "CannyAutoThres.h"
#include "main.h"
#include "CannyAutoThres_terminate.h"
#include "CannyAutoThres_initialize.h"

// Function Declarations
static void argInit_800x800_real32_T(float result[640000]);
static float argInit_real32_T();
static void main_CannyAutoThres();

// Function Definitions

//
// Arguments    : float result[640000]
// Return Type  : void
//
static void argInit_800x800_real32_T(float result[640000])
{
  int idx0;
  int idx1;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 800; idx0++) {
    for (idx1 = 0; idx1 < 800; idx1++) {
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
static void main_CannyAutoThres()
{
  static float fv6[640000];
  static boolean_T outputImage[640000];

  // Initialize function 'CannyAutoThres' input arguments.
  // Initialize function input argument 'inputImage'.
  // Call the entry-point 'CannyAutoThres'.
  argInit_800x800_real32_T(fv6);
  CannyAutoThres(fv6, outputImage);
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
  CannyAutoThres_initialize();

  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_CannyAutoThres();

  // Terminate the application.
  // You do not need to do this more than one time.
  CannyAutoThres_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
