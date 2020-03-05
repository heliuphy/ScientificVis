
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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << argv[0] << " " << "ImageFile(*.png)" << std::endl;
        return EXIT_FAILURE;
    }
    vtkSmartPointer<vtkPNGReader> reader =
            vtkSmartPointer<vtkPNGReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();

    vtkSmartPointer<vtkImageLaplacian> lapFilter =
            vtkSmartPointer<vtkImageLaplacian>::New();
    lapFilter->SetInputConnection(reader->GetOutputPort());
    lapFilter->SetDimensionality(2);

    double range[2];
    lapFilter->GetOutput()->GetScalarRange(range);

    vtkSmartPointer<vtkImageShiftScale> ShiftScale =
            vtkSmartPointer<vtkImageShiftScale>::New();
    ShiftScale->SetOutputScalarTypeToUnsignedChar();
    ShiftScale->SetScale(255 / (range[1] - range[0]));
    ShiftScale->SetShift(-range[0]);
    ShiftScale->SetInputConnection(lapFilter->GetOutputPort());
    ShiftScale->Update();

    vtkSmartPointer<vtkImageActor> originalActor =
            vtkSmartPointer<vtkImageActor>::New();
    originalActor->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkImageActor> gradActor =
            vtkSmartPointer<vtkImageActor>::New();
    gradActor->SetInputData(ShiftScale->GetOutput());

    double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
    double gradviewport[4] = {0.5, 0.0, 1.0, 1.0};

    vtkSmartPointer<vtkRenderer> originalRenderer =
            vtkSmartPointer<vtkRenderer>::New();
    originalRenderer->SetViewport(originalViewport);
    originalRenderer->AddActor(originalActor);
    originalRenderer->ResetCamera();
    originalRenderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderer> gradRenderer =
            vtkSmartPointer<vtkRenderer>::New();
    gradRenderer->SetViewport(gradviewport);
    gradRenderer->AddActor(gradActor);
    gradRenderer->ResetCamera();
    gradRenderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindow =
            vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(originalRenderer);
    renderWindow->AddRenderer(gradRenderer);
    renderWindow->SetSize(640, 320);
    renderWindow->Render();
    renderWindow->SetWindowName("LaplacianExample");

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleImage> style =
            vtkSmartPointer<vtkInteractorStyleImage>::New();

    renderWindowInteractor->SetInteractorStyle(style);
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
