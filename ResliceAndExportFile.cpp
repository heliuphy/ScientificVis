//
// Created by 何柳 on 2020/3/5.
//
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkMatrix4x4.h>
#include <vtkImageReslice.h>
#include <iostream>
#include <vtkMetaImageReader.h>
#include <vtkMetaImageWriter.h>
#include <vtkImageReader2.h>
#include <ctime>
#include <vtkGenericDataObjectReader.h>

using std::cout;
using std::endl;

int main(int argc, char **argv) {
    // Read Input File
    if (argc != 3) {
        cout << "./program input.vtk output.vtk" << endl;
        return EXIT_FAILURE;
    }
    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(argv[1]);

    cout << "Reading file ... " << endl;
    clock_t start, end;
    start = clock();
    reader->Update();
    end = clock();
    cout << "Reading finished, time spend " << (double) (end - start) / CLOCKS_PER_SEC << " s" << endl;

    vtkSmartPointer<vtkImageData> imageData =
            vtkSmartPointer<vtkImageData>::New();
    imageData = reader->GetOutput();

    cout << "number of points: " << imageData->GetNumberOfPoints() << endl;
    cout << "number of scalar components:  " << imageData->GetNumberOfScalarComponents() << endl;

    // Compute information needed for slicing
    int extent[6];
    double spacing[3];
    double origin[3];
    double center[3];

    imageData->GetExtent(extent);
    imageData->GetSpacing(spacing);
    imageData->GetOrigin(origin);

    center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
    center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
    center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);

    // Define slice matrix
    static double axialElements[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    };

    vtkSmartPointer<vtkMatrix4x4> resliceAxes =
            vtkSmartPointer<vtkMatrix4x4>::New();
    resliceAxes->DeepCopy(axialElements);
    resliceAxes->SetElement(0, 3, center[0]);
    resliceAxes->SetElement(1, 3, center[1]);
    resliceAxes->SetElement(2, 3, center[2]);

    vtkSmartPointer<vtkImageReslice> reslice =
            vtkSmartPointer<vtkImageReslice>::New();

    reslice->SetInputConnection(reader->GetOutputPort());
    reslice->SetOutputDimensionality(2);
    reslice->SetResliceAxes(resliceAxes);
    reslice->SetInterpolationModeToLinear();

    vtkSmartPointer<vtkMetaImageWriter> writer =
            vtkSmartPointer<vtkMetaImageWriter>::New();
    writer->SetInputConnection(reslice->GetOutputPort());
    writer->SetFileName(argv[2]);
    writer->Write();

    return EXIT_SUCCESS;
}
