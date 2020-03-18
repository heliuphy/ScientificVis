//
// Created by 何柳 on 2020/3/14.
//
#include "ImageFill_types.h"
#include "rtwtypes.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkPNGWriter.h>
#include "HlwUtils.h"


int main(int argc, char **argv) {
    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
//    reader->Print(cout);

    vtkSmartPointer<vtkMetaImageReader> planeReader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    planeReader->SetFileName(argv[2]);
    planeReader->Update();
//    planeReader->Print(cout);

    vtkSmartPointer<vtkImageData> input3DImageData = reader->GetOutput();
    vtkSmartPointer<vtkImageData> planeImageData = planeReader->GetOutput();


    double input3DOrigin[3];
    double input3DSpacing[3];
    int input3DExtent[6];

    input3DImageData->GetOrigin(input3DOrigin);
    input3DImageData->GetSpacing(input3DSpacing);
    input3DImageData->GetExtent(input3DExtent);

    double tempPlaneOrigin[3];
    double tempPlaneSpacing[3];
    int tempPlaneExtent[6];


    planeImageData->GetOrigin(tempPlaneOrigin);
    planeImageData->GetSpacing(tempPlaneSpacing);
    planeImageData->GetExtent(tempPlaneExtent);

    float *tempPlanePointer = nullptr;

    vtkSmartPointer<vtkImageData> afterCannyImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterCannyImageData->SetOrigin(planeImageData->GetOrigin());
    afterCannyImageData->SetExtent(planeImageData->GetExtent());
    afterCannyImageData->SetSpacing(planeImageData->GetSpacing());
    afterCannyImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
//    afterCannyImageData->Print(cout);


    vtkSmartPointer<vtkImageData> afterCannyAndFillImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterCannyAndFillImageData->SetOrigin(planeImageData->GetOrigin());
    afterCannyAndFillImageData->SetExtent(planeImageData->GetExtent());
    afterCannyAndFillImageData->SetSpacing(planeImageData->GetSpacing());
    afterCannyAndFillImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
//    afterCannyAndFillImageData->Print(cout);

    vtkSmartPointer<vtkImageData> afterSubImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterSubImageData->SetOrigin(planeImageData->GetOrigin());
    afterSubImageData->SetExtent(planeImageData->GetExtent());
    afterSubImageData->SetSpacing(planeImageData->GetSpacing());
    afterSubImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
//    afterSubImageData->Print(cout);

    auto afterSubDataPointer = (boolean_T *) (afterSubImageData->GetScalarPointer());


    vtkSmartPointer<vtkImageData> multiply255 =
            vtkSmartPointer<vtkImageData>::New();
    multiply255->SetOrigin(planeImageData->GetOrigin());
    multiply255->SetExtent(planeImageData->GetExtent());
    multiply255->SetSpacing(planeImageData->GetSpacing());
    multiply255->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
//    multiply255->Print(cout);

    auto multiply255DataPointer = (boolean_T *) (multiply255->GetScalarPointer());

    vtkSmartPointer<vtkPNGWriter> writer =
            vtkSmartPointer<vtkPNGWriter>::New();

    int zIndexes[100];
    zIndexes[0] = 0;
    for (int i = 1; i < 100; i++) {
        zIndexes[i] = 399 - 4 * (i - 1);
    }
//    , 449, 499, 549, 599, 649, 699, 749, 799
    for (int i = 0; i < 100; i++) {
        // Extract plane from input 3d image data
        tempPlaneExtent[4] = zIndexes[i];
        tempPlaneExtent[5] = zIndexes[i];
        tempPlanePointer = (float *) (input3DImageData->GetScalarPointerForExtent(tempPlaneExtent));

        planeBoundaryDetection(tempPlanePointer,
                               afterCannyImageData,
                               afterCannyAndFillImageData,
                               afterSubImageData,
                               CANNY_FILL_AND_SUB);

        booleanTArrayMultiplyByK((boolean_T *) (afterSubImageData->GetScalarPointer()), multiply255DataPointer, 255,
                                 800, 800);

        std::string _filename;
        _filename = "/Users/heliu/temp/node-centered/step3-3d/" + std::to_string(zIndexes[i]) + ".png";
        writer->SetFileName(_filename.c_str());
        writer->SetInputData(multiply255);
        writer->Write();
//        writer->Print(cout);
        cout << i << ".png" << "  has been written \n";
    }

    return 0;
}
