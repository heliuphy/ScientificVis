//
// Created by 何柳 on 2020/3/6.
//
#include <vtkSmartPointer.h>

#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkActor.h>
#include <vtkBarChartActor.h>
#include <vtkFieldData.h>
#include <vtkImageAccumulate.h>
#include <vtkImageData.h>
#include <vtkImageExtractComponents.h>
#include <vtkIntArray.h>
#include <vtkLegendBoxActor.h>
#include <vtkProperty2D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageMagnitude.h>
#include <vtkNamedColors.h>
#include <vtkMetaImageReader.h>

int main(int argc, char *argv[]) {
    // Handle the arguments
    if (argc < 2) {
        std::cout << "Required arguments: filename" << std::endl;
        return EXIT_FAILURE;
    }

    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();

//  vtkSmartPointer<vtkImageMagnitude> magnitude =
//    vtkSmartPointer<vtkImageMagnitude>::New();
//  magnitude->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkNamedColors> colors =
            vtkSmartPointer<vtkNamedColors>::New();

    vtkSmartPointer<vtkIntArray> frequencies =
            vtkSmartPointer<vtkIntArray>::New();

    vtkSmartPointer<vtkImageAccumulate> histogram =
            vtkSmartPointer<vtkImageAccumulate>::New();
    histogram->SetInputConnection(reader->GetOutputPort());
    histogram->SetComponentExtent(0, 100000, 0, 0, 0, 0);
    histogram->SetComponentOrigin(0, 0, 0);
    histogram->SetComponentSpacing(1, 0, 0);
    histogram->IgnoreZeroOn();
    histogram->Update();

    int numberOfTuples = 64;
    frequencies->SetNumberOfComponents(1);
    frequencies->SetNumberOfTuples(numberOfTuples);
    vtkIdType *output = static_cast<vtkIdType *>(histogram->GetOutput()->GetScalarPointer());

    for (int j = 0; j < numberOfTuples; ++j) {
        frequencies->SetTuple1(j, *output++);
    }

    vtkSmartPointer<vtkDataObject> dataObject =
            vtkSmartPointer<vtkDataObject>::New();

    dataObject->GetFieldData()->AddArray(frequencies);

    // Create a vtkBarChartActor
    vtkSmartPointer<vtkBarChartActor> barChart =
            vtkSmartPointer<vtkBarChartActor>::New();

    barChart->SetInput(dataObject);
    barChart->SetTitle("Histogram");
    barChart->GetPositionCoordinate()->SetValue(0.1, 0.05, 0.0);
    barChart->GetPosition2Coordinate()->SetValue(0.95, 0.85, 0.0);
    barChart->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
    barChart->GetLegendActor()->SetNumberOfEntries(
            dataObject->GetFieldData()->GetArray(0)->GetNumberOfTuples());
    barChart->LegendVisibilityOff();
    barChart->LabelVisibilityOff();

    int count = 0;
    for (int i = 0; i < numberOfTuples; ++i) {
        barChart->SetBarColor(count++, colors->GetColor3d("Tomato").GetData());
    }

    // Visualize the histogram
    vtkSmartPointer<vtkRenderer> renderer =
            vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(barChart);
    renderer->SetBackground(colors->GetColor3d("Peacock").GetData());
    vtkSmartPointer<vtkRenderWindow> renderWindow =
            vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(640, 480);

    vtkSmartPointer<vtkRenderWindowInteractor> interactor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

    // Initialize the event loop and then start it
    renderWindow->Render();
    interactor->Initialize();
    interactor->Start();

    return EXIT_SUCCESS;
}
