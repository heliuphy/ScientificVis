/**
 * run ok
 * input data format is vtkRectilinearGrid (3D)
 * output data format is vtkPolyData (2D)
 * output size is about 10MB
 */

#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkRectilinearGridReader.h>
#include <vtkPlane.h>
#include <vtkCutter.h>
#include <iostream>
#include <vtkPolyDataWriter.h>

int main(int argc, char **argv) {

    if (argc != 3) {
        std::cout << "./SliceUsingCutter inputfile outputfile" << endl;
        return EXIT_FAILURE;
    }

    vtkSmartPointer<vtkRectilinearGridReader> reader =
            vtkSmartPointer<vtkRectilinearGridReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();

    vtkSmartPointer<vtkPlane> plane =
            vtkSmartPointer<vtkPlane>::New();
    plane->SetOrigin(0, 0, 1000);
    // XZ =(1,0,0);XY =(0,0,1),YZ =(0,1,0)
    // Here XY
    plane->SetNormal(0, 0, 1);

    vtkSmartPointer<vtkCutter> cutter =
            vtkSmartPointer<vtkCutter>::New();
    cutter->SetCutFunction(plane);
    cutter->SetInputConnection(reader->GetOutputPort());
    cutter->Update();

    vtkSmartPointer<vtkPolyDataWriter> writer =
            vtkSmartPointer<vtkPolyDataWriter>::New();
    writer->SetFileName(argv[2]);
    writer->SetInputConnection(cutter->GetOutputPort());
    writer->Write();

    return EXIT_SUCCESS;

}
