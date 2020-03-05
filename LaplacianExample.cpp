
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageShiftScale.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkJPEGReader.h>
#include <vtkImageLaplacian.h>
#include <vtkPNGReader.h>
#include <vtkMetaImageReader.h>
#include <vtkMetaImageWriter.h>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "./program file1.mhd file2" << endl;
        return EXIT_FAILURE;
    }

    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();

    vtkSmartPointer<vtkImageLaplacian> lapFilter =
            vtkSmartPointer<vtkImageLaplacian>::New();
    lapFilter->SetInputConnection(reader->GetOutputPort());
    lapFilter->SetDimensionality(2);

    double range[2];
    lapFilter->GetOutput()->GetScalarRange(range);

//    vtkSmartPointer<vtkImageShiftScale> ShiftScale =
//            vtkSmartPointer<vtkImageShiftScale>::New();
//    ShiftScale->SetOutputScalarTypeToUnsignedChar();
//    ShiftScale->SetScale(255 / (range[1] - range[0]));
//    ShiftScale->SetShift(-range[0]);
//    ShiftScale->SetInputConnection(lapFilter->GetOutputPort());
//    ShiftScale->Update();

    vtkSmartPointer<vtkMetaImageWriter> writer =
        vtkSmartPointer<vtkMetaImageWriter>::New();
    writer->SetFileName(argv[2]);
    writer->SetInputConnection(lapFilter->GetOutputPort());
    writer->Write();

    return EXIT_SUCCESS;
}
