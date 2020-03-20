// Include Files
#include "rt_nonfinite.h"
#include "CannyAutoThres_X.h"
#include "main.h"
#include "CannyAutoThres_X_terminate.h"
#include "CannyAutoThres_X_emxAPI.h"
#include "CannyAutoThres_X_initialize.h"

static float argInit_real32_T();

static emxArray_real32_T *c_argInit_UnboundedxUnbounded_r();

static void main_CannyAutoThres_X();

static float argInit_real32_T() {
    return 0.0F;
}

static emxArray_real32_T *c_argInit_UnboundedxUnbounded_r() {
    emxArray_real32_T *result;
    static int iv1[2] = {2, 2};

    int idx0;
    int idx1;

    // Set the size of the array.
    // Change this size to the value that the application requires.
    result = emxCreateND_real32_T(2, *(int (*)[2]) &iv1[0]);

    // Loop over the array to initialize each element.
    for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
        for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
            // Set the value of the array element.
            // Change this value to the value that the application requires.
            result->data[idx0 + result->size[0] * idx1] = argInit_real32_T();
        }
    }

    return result;
}

static void main_CannyAutoThres_X() {
    emxArray_boolean_T *outputImage;
    emxArray_real32_T *inputImage;
    emxInitArray_boolean_T(&outputImage, 2);

    // Initialize function 'CannyAutoThres_X' input arguments.
    // Initialize function input argument 'inputImage'.
    inputImage = c_argInit_UnboundedxUnbounded_r();

    // Call the entry-point 'CannyAutoThres_X'.
    CannyAutoThres_X(inputImage, outputImage);
    emxDestroyArray_boolean_T(outputImage);
    emxDestroyArray_real32_T(inputImage);
}

int main(int, const char *const[]) {
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

