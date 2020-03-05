#include <iostream>
#include <vtkColorTransferFunction.h>
#include <vtkDataObject.h>
#include <vtkGenericDataObjectReader.h>
#include <vtkImageCast.h>
#include <vtkPiecewiseFunction.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkVolumeRayCastMapper.h>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {

  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
      vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();

  renWin->AddRenderer(ren);
  iren->SetRenderWindow(renWin);

  // reader
  vtkSmartPointer<vtkGenericDataObjectReader> reader =
      vtkSmartPointer<vtkGenericDataObjectReader>::New();
  reader->SetFileName("/Users/heliu/temp/node-centered/cjbImagebin.vtk");

  // Cast Float Array to unsignedShort
  vtkSmartPointer<vtkImageCast> cast = vtkSmartPointer<vtkImageCast>::New();
  cast->SetInputConnection(reader->GetOutputPort());
  cast->SetOutputScalarTypeToUnsignedShort();
  vtkDataObject *output = cast->GetOutputDataObject(reader->GetOutputPort());
  cout << output->GetInformation() << endl;
  //
  //    // transfer function
  //    vtkSmartPointer<vtkPiecewiseFunction> opacityFun =
  //        vtkSmartPointer<vtkPiecewiseFunction>::New();
  //    opacityFun->AddPoint(0.0, 0.0);
  //    opacityFun->AddPoint(2.42128e7, 1.0);
  //
  //    vtkSmartPointer<vtkColorTransferFunction> colorFun =
  //        vtkSmartPointer<vtkColorTransferFunction>::New();
  //    colorFun->AddRGBPoint(0, 0.231373, 0.298039, 0.752941);
  //    colorFun->AddRGBPoint(1.21064e+07, 0.865003, 0.865003, 0.865003);
  //    colorFun->AddRGBPoint(2.42128e7, 0.705882, 0.0156863, 0.14902);
  //
  //    vtkSmartPointer<vtkVolumeProperty> property =
  //        vtkSmartPointer<vtkVolumeProperty>::New();
  //    property->SetScalarOpacity(opacityFun);
  //    property->SetColor(colorFun);
  //    property->SetInterpolationTypeToLinear();
  //
  //    vtkSmartPointer<vtkVolumeRayCastMapper> mapper =
  //        vtkSmartPointer<vtkVolumeRayCastMapper>::New();
  //    vtkSmartPointer<vtkVolumeRayCastCompositeFunction> rayFun =
  //        vtkSmartPointer<vtkVolumeRayCastCompositeFunction>::New();
  //    mapper->SetVolumeRayCastFunction(rayFun);
  //    mapper->SetInputConnection(cast->GetOutputPort());
  //
  //    vtkSmartPointer<vtkVolume> volume =
  //        vtkSmartPointer<vtkVolume>::New();
  //    volume->SetMapper(mapper);
  //    volume->SetProperty(property);
  //
  //    ren->AddVolume(volume);
  //    ren->SetBackground(0, 0, 0);
  //    renWin->SetSize(600, 600);
  //
  //    iren->Initialize();
  //    renWin->Render();
  //    iren->Start();
  //
  //
  return 0;
}
