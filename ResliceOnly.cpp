#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkMatrix4x4.h>
#include <vtkImageReslice.h>
#include <iostream>
#include <vtkMetaImageReader.h>
#include <vtkMetaImageWriter.h>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    bool printInfo = false;
    bool renderImage = true;
    bool slice = true;

    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName("/Users/heliu/temp/node-centered/cjbMetaImage.mhd");
    reader->SetDataScalarTypeToUnsignedShort();
    reader->Update();

    if (printInfo) {

        cout << "number of components: " << reader->GetNumberOfComponents() << endl;
        cout << "number of output ports: " << reader->GetNumberOfOutputPorts() << endl;
        cout << "number of scalar components:  " << reader->GetNumberOfScalarComponents() << endl;
    }
    int extent[6];
    double spacing[3];
    double origin[3];

    reader->GetOutput()->GetExtent(extent);
    reader->GetOutput()->GetSpacing(spacing);
    reader->GetOutput()->GetOrigin(origin);

    if (printInfo) {

        cout << "extent: " << endl;
        for (int i = 0; i < 6; i++) {
            cout << extent[i] << " ";
        }

        cout << endl;
        cout << "spacing: " << endl;
        for (int i = 0; i < 3; i++) {
            cout << spacing[i] << " ";
        }

        cout << endl;
        cout << "origin: " << endl;
        for (int i = 0; i < 3; i++) {
            cout << origin[i] << " ";
        }
        cout << endl;
    }

    double center[3];
    center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
    center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
    center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);

    if (printInfo) {

        cout << endl;
        cout << "center: " << endl;
        for (int i = 0; i < 3; i++) {
            cout << center[i] << " ";
        }
        cout << endl;
    }




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
    writer->SetFileName("/Users/heliu/temp/node-centered/cjbSliceMetaImage.mhd");
    writer->Write();

    return 0;
}
