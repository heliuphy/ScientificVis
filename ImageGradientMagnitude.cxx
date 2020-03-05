//
// Created by 何柳 on 2020/3/5.
//
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageGradientMagnitude.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageCast.h>
#include <vtkMetaImageReader.h>
#include <vtkMetaImageWriter.h>

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

    vtkSmartPointer<vtkImageGradientMagnitude> gradientMagnitudeFilter =
            vtkSmartPointer<vtkImageGradientMagnitude>::New();
    gradientMagnitudeFilter->SetInputConnection(reader->GetOutputPort());
    gradientMagnitudeFilter->Update();

//    vtkSmartPointer<vtkImageCast> gradientMagnitudeCastFilter =
//            vtkSmartPointer<vtkImageCast>::New();
//    gradientMagnitudeCastFilter->SetInputConnection(gradientMagnitudeFilter->GetOutputPort());
//    gradientMagnitudeCastFilter->SetOutputScalarTypeToUnsignedShort();
//    gradientMagnitudeCastFilter->Update();

    vtkSmartPointer<vtkMetaImageWriter> writer =
            vtkSmartPointer<vtkMetaImageWriter>::New();
    writer->SetInputConnection(gradientMagnitudeFilter->GetOutputPort());
    writer->SetFileName(argv[2]);
    writer->Write();

    return EXIT_SUCCESS;
}
