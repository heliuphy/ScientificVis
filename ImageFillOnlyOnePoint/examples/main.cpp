// Include Files
#include "rt_nonfinite.h"
#include "ImageFillOnlyOnePoint.h"
#include "print100plane.h"
#include "ImageFillOnlyOnePoint_terminate.h"
#include "ImageFillOnlyOnePoint_initialize.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkPNGReader.h>
#include <vtkPNGWriter.h>

// Function Declarations
static void argInit_800x800_boolean_T(boolean_T result[640000]);

static boolean_T argInit_boolean_T();

static double argInit_real_T();

static void main_ImageFillOnlyOnePoint();

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
static void main_ImageFillOnlyOnePoint() {
    static boolean_T bv0[640000];
    static boolean_T outputImage[640000];

    // Initialize function 'ImageFillOnlyOnePoint' input arguments.
    // Initialize function input argument 'inputImage'.
    // Call the entry-point 'ImageFillOnlyOnePoint'.
    argInit_800x800_boolean_T(bv0);
    ImageFillOnlyOnePoint(bv0, argInit_real_T(), outputImage);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int, const char *const[]) {
    // Initialize the application.
    // You do not need to do this more than one time.
    ImageFillOnlyOnePoint_initialize();

    // Invoke the entry-point functions.
    // You can call entry-point functions multiple times.

    vtkSmartPointer<vtkPNGReader> reader =
            vtkSmartPointer<vtkPNGReader>::New();
    reader->SetFileName("/Users/heliu/temp/node-centered/step3-3d/100-canny/127.png");
    reader->Update();

    vtkSmartPointer<vtkImageData> output =
            vtkSmartPointer<vtkImageData>::New();
    output->SetOrigin(0, 0, 0);
    output->SetSpacing(5, 5, 5);
    output->SetExtent(0, 799, 0, 799, 0, 0);
    output->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    auto inputPointer = (boolean_T *)(reader->GetOutput()->GetScalarPointer());
    auto outputPointer = (boolean_T *)(output->GetScalarPointer());

    double id = 500;

    ImageFillOnlyOnePoint(inputPointer, id, outputPointer);

    for (int j = 0; j < 640000; j++) {
            *outputPointer = *outputPointer * 255;
            outputPointer++;
    }

    vtkSmartPointer<vtkPNGWriter> writer =
        vtkSmartPointer<vtkPNGWriter>::New();
    writer->SetFileName("/Users/heliu/temp/node-centered/step3-3d/test/out.png");
    writer->SetInputData(output);
    writer->Write();

    // Terminate the application.
    // You do not need to do this more than one time.
    ImageFillOnlyOnePoint_terminate();
    return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
