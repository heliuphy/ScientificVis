#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkStructuredPoints.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageLuminance.h>
#include <vtkProperty.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkImageCast.h>
#include <vtkImageGradient.h>
#include <vtkImageMagnitude.h>
#include <vtkImageNonMaximumSuppression.h>
#include <vtkImageConstantPad.h>
#include <vtkImageToStructuredPoints.h>
#include <vtkLinkEdgels.h>
#include <vtkThreshold.h>
#include <vtkGeometryFilter.h>
#include <vtkSubPixelPositionEdgels.h>
#include <vtkStripper.h>
#include <vtkPolyDataMapper.h>
#include <vtkCamera.h>
#include <vtkJPEGReader.h>
#include <vtkImageReader2Factory.h>
#include <iostream>
#include <vtkMetaImageReader.h>
#include <vtkMetaImageWriter.h>
#include <vtkPolyDataWriter.h>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {

    if (argc != 3) {
        cout << "./Program input.mhd output.mhd" << std::endl;
        return EXIT_FAILURE;
    }

    vtkSmartPointer<vtkMetaImageReader> reader =
        vtkSmartPointer<vtkMetaImageReader>::New();

    reader->SetFileName(argv[1]);
    reader->Update();


//    vtkSmartPointer<vtkImageLuminance> il =
//            vtkSmartPointer<vtkImageLuminance>::New();
//    il->SetInputConnection(imageIn->GetOutputPort());
//
//    vtkSmartPointer<vtkImageCast> ic =
//            vtkSmartPointer<vtkImageCast>::New();
//    ic->SetOutputScalarTypeToFloat();
//    ic->SetInputConnection(il->GetOutputPort());

    // Smooth the image
    vtkSmartPointer<vtkImageGaussianSmooth> gs =
            vtkSmartPointer<vtkImageGaussianSmooth>::New();
    gs->SetInputConnection(reader->GetOutputPort());
    gs->SetDimensionality(2);
    gs->SetRadiusFactors(1, 1, 0);

    // Gradient the image
    vtkSmartPointer<vtkImageGradient> imgGradient =
            vtkSmartPointer<vtkImageGradient>::New();
    imgGradient->SetInputConnection(gs->GetOutputPort());
    imgGradient->SetDimensionality(2);

    vtkSmartPointer<vtkImageMagnitude> imgMagnitude =
            vtkSmartPointer<vtkImageMagnitude>::New();
    imgMagnitude->SetInputConnection(imgGradient->GetOutputPort());

    // Non maximum suppression
    vtkSmartPointer<vtkImageNonMaximumSuppression> nonMax =
            vtkSmartPointer<vtkImageNonMaximumSuppression>::New();
    imgMagnitude->Update();
    nonMax->SetMagnitudeInputData(imgMagnitude->GetOutput());
    imgGradient->Update();
    nonMax->SetVectorInputData(imgGradient->GetOutput());
    nonMax->SetDimensionality(2);

    vtkSmartPointer<vtkImageConstantPad> pad =
            vtkSmartPointer<vtkImageConstantPad>::New();
    pad->SetInputConnection(imgGradient->GetOutputPort());
    pad->SetOutputNumberOfScalarComponents(3);
    pad->SetConstant(0);

    vtkSmartPointer<vtkImageToStructuredPoints> i2sp1 =
            vtkSmartPointer<vtkImageToStructuredPoints>::New();
    i2sp1->SetInputConnection(nonMax->GetOutputPort());
    pad->Update();
    i2sp1->SetVectorInputData(pad->GetOutput());

    // Link edgles
    vtkSmartPointer<vtkLinkEdgels> imgLink =
            vtkSmartPointer<vtkLinkEdgels>::New();
    imgLink->SetInputConnection(i2sp1->GetOutputPort());
    imgLink->SetGradientThreshold(2);

    // Threshold links
    vtkSmartPointer<vtkThreshold> thresholdEdgels =
            vtkSmartPointer<vtkThreshold>::New();
    thresholdEdgels->SetInputConnection(imgLink->GetOutputPort());
    thresholdEdgels->ThresholdByUpper(10);
    thresholdEdgels->AllScalarsOff();

    vtkSmartPointer<vtkGeometryFilter> gf =
            vtkSmartPointer<vtkGeometryFilter>::New();
    gf->SetInputConnection(thresholdEdgels->GetOutputPort());

    vtkSmartPointer<vtkImageToStructuredPoints> i2sp =
            vtkSmartPointer<vtkImageToStructuredPoints>::New();
    i2sp->SetInputConnection(imgMagnitude->GetOutputPort());
    pad->Update();
    i2sp->SetVectorInputData(pad->GetOutput());

    // Subpixel them
    vtkSmartPointer<vtkSubPixelPositionEdgels> spe =
            vtkSmartPointer<vtkSubPixelPositionEdgels>::New();
    spe->SetInputConnection(gf->GetOutputPort());
    i2sp->Update();
    spe->SetGradMapsData(i2sp->GetStructuredPointsOutput());

    vtkSmartPointer<vtkStripper> strip =
            vtkSmartPointer<vtkStripper>::New();
    strip->SetInputConnection(spe->GetOutputPort());

    vtkSmartPointer<vtkPolyDataWriter> writer =
        vtkSmartPointer<vtkPolyDataWriter>::New();

    writer->SetFileName(argv[2]);
    writer->SetInputConnection(strip->GetOutputPort());
    writer->Write();

    return EXIT_SUCCESS;
}
