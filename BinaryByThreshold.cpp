//
// Created by 何柳 on 2020/3/6.
//
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <iostream>
#include <vtkMetaImageReader.h>
#include <vtkImageIterator.h>
#include <vtkMetaImageWriter.h>

using std::cout;
using std::endl;

template<class T>
void printArray(T *array, int length) {
    for (int i = 0; i < length; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int main(int argc, char **argv) {

    if (argc != 3) {
        std::cout << argv[0] << " " << " file 1   file2 " << endl;
        return EXIT_FAILURE;
    }
    int minThreshold = 47692;
    int maxThreshold = 333749;
    int windowWidth = 1000;

    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();

    // Get original image information
    int extent[6];
    double spacing[3];
    double origin[3];

    vtkImageData* originalImageData = reader->GetOutput();
    originalImageData->GetExtent(extent);
    originalImageData->GetSpacing(spacing);
    originalImageData->GetOrigin(origin);

    cout << "extent: ";
    printArray<int>(extent, 6);
    cout << "spacing: ";
    printArray<double>(spacing, 3);
    cout << "origin: ";
    printArray<double>(origin, 3);

    // Create binary image
    vtkSmartPointer<vtkImageData> binaryImage =
            vtkSmartPointer<vtkImageData>::New();
    binaryImage->SetExtent(extent);
    binaryImage->SetSpacing(spacing);
    binaryImage->SetOrigin(origin);
    binaryImage->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    int dims[3];
    originalImageData->GetDimensions(dims);
    for (int k = 0; k < dims[2]; k++) {
        for (int j = 0; j < dims[1]; j++) {
            for (int i = 0; i < dims[0]; i++) {
                float *originalPixel = (float *) (originalImageData->GetScalarPointer(i, j, k));
                unsigned char *binaryPixel = (unsigned char *) (binaryImage->GetScalarPointer(i, j, k));
                if (*originalPixel >= (minThreshold - windowWidth)) {
                    *binaryPixel = 255;
                } else {
                    *binaryPixel = 0;
                }
            }
        }
    }

    vtkSmartPointer<vtkMetaImageWriter> writer =
            vtkSmartPointer<vtkMetaImageWriter>::New();
    writer->SetFileName(argv[2]);
    writer->SetInputData(binaryImage);
    writer->Write();

    return EXIT_SUCCESS;
}
