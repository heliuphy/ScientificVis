
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkJPEGReader.h>
#include <vtkImageGradient.h>
#include <vtkImageMagnitude.h>
#include <vtkImageCast.h>
#include <vtkImageShiftScale.h>
#include <vtkMetaImageReader.h>
#include <vtkPNGReader.h>
#include <vtkImageLuminance.h>
#include <vtkMetaImageWriter.h>

int main(int argc, char *argv[]) {
//    vtkSmartPointer<vtkPNGReader> reader =
//            vtkSmartPointer<vtkPNGReader>::New();

    if (argc != 3) {
        std::cout << "./xx file1 file2 " << endl;
        return EXIT_FAILURE;
    }

    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();

//    vtkSmartPointer<vtkImageLuminance> luminance =
//            vtkSmartPointer<vtkImageLuminance>::New();
//    luminance->SetInputConnection(reader->GetOutputPort());
//    luminance->Update();

    vtkSmartPointer<vtkImageGradient> gradientFilter =
            vtkSmartPointer<vtkImageGradient>::New();
//    gradientFilter->SetInputConnection(luminance->GetOutputPort());
    gradientFilter->SetInputConnection(reader->GetOutputPort());
    gradientFilter->SetDimensionality(2);

    vtkSmartPointer<vtkImageMagnitude> magnitudeFilter =
            vtkSmartPointer<vtkImageMagnitude>::New();
    magnitudeFilter->SetInputConnection(gradientFilter->GetOutputPort());
    magnitudeFilter->Update();

    double range[2];
    magnitudeFilter->GetOutput()->GetScalarRange(range);
    std::cout << "range : " << range[0] << "   " << range[1] << std::endl;

    vtkSmartPointer<vtkImageShiftScale> ShiftScale =
            vtkSmartPointer<vtkImageShiftScale>::New();
    ShiftScale->SetOutputScalarTypeToUnsignedShort();
    ShiftScale->SetScale(65535 / range[1]);
    ShiftScale->SetInputConnection(magnitudeFilter->GetOutputPort());
    ShiftScale->Update();

    vtkSmartPointer<vtkMetaImageWriter> writer =
            vtkSmartPointer<vtkMetaImageWriter>::New();
    writer->SetInputConnection(ShiftScale->GetOutputPort());
    writer->SetFileName(argv[2]);
    writer->Write();
//    vtkSmartPointer<vtkImageActor> originalActor =
//            vtkSmartPointer<vtkImageActor>::New();
//    originalActor->SetInputData(reader->GetOutput());
//
//    vtkSmartPointer<vtkImageActor> gradActor =
//            vtkSmartPointer<vtkImageActor>::New();
//    gradActor->SetInputData(ShiftScale->GetOutput());
//
////	double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
////	double gradviewport[4] = {0.5, 0.0, 1.0, 1.0};
////
////	vtkSmartPointer<vtkRenderer> originalRenderer =
////		vtkSmartPointer<vtkRenderer>::New();
////	originalRenderer->SetViewport(originalViewport);
////	originalRenderer->AddActor(originalActor);
////	originalRenderer->ResetCamera();
////	originalRenderer->SetBackground(1.0, 1.0, 1.0);
//
//    vtkSmartPointer<vtkRenderer> gradRenderer =
//            vtkSmartPointer<vtkRenderer>::New();
////	gradRenderer->SetViewport(gradviewport);
//    gradRenderer->AddActor(gradActor);
//    gradRenderer->ResetCamera();
//    gradRenderer->SetBackground(1.0, 1.0, 1.0);
//
//    vtkSmartPointer<vtkRenderWindow> renderWindow =
//            vtkSmartPointer<vtkRenderWindow>::New();
////	renderWindow->AddRenderer(originalRenderer);
//    renderWindow->AddRenderer(gradRenderer);
//    renderWindow->SetSize(1024, 768);
//    renderWindow->Render();
//    renderWindow->SetWindowName("ImageGradientExample");
//
//    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
//            vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    vtkSmartPointer<vtkInteractorStyleImage> style =
//            vtkSmartPointer<vtkInteractorStyleImage>::New();
//
//    renderWindowInteractor->SetInteractorStyle(style);
//    renderWindowInteractor->SetRenderWindow(renderWindow);
//    renderWindowInteractor->Initialize();
//    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
