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

    float *inputTempPlanePointer = nullptr;

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


//    vtkSmartPointer<vtkImageData> multiply255 =
//            vtkSmartPointer<vtkImageData>::New();
//    multiply255->SetOrigin(planeImageData->GetOrigin());
//    multiply255->SetExtent(planeImageData->GetExtent());
//    multiply255->SetSpacing(planeImageData->GetSpacing());
//    multiply255->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
////    multiply255->Print(cout);

//    auto multiply255DataPointer = (boolean_T *) (multiply255->GetScalarPointer());

    vtkSmartPointer<vtkImageData> output3dEdgeData =
            vtkSmartPointer<vtkImageData>::New();
    output3dEdgeData->SetExtent(reader->GetOutput()->GetExtent());
    output3dEdgeData->SetOrigin(reader->GetOutput()->GetOrigin());
    output3dEdgeData->SetSpacing(reader->GetOutput()->GetSpacing());
    output3dEdgeData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    int zIndexes[400];
    for (int i = 0; i < 400; i++) {
        zIndexes[i] = i;
    }
//    , 449, 499, 549, 599, 649, 699, 749, 799
    for (int i = 0; i < 400; i++) {
        // Extract plane from input 3d image data
        tempPlaneExtent[4] = zIndexes[i];
        tempPlaneExtent[5] = zIndexes[i];
        inputTempPlanePointer = (float *) (input3DImageData->GetScalarPointerForExtent(tempPlaneExtent));

        planeBoundaryDetection(inputTempPlanePointer,
                               afterCannyImageData,
                               afterCannyAndFillImageData,
                               afterSubImageData,
                               CANNY_FILL_AND_SUB);

        auto afterSubPointer = (boolean_T *) (afterSubImageData->GetScalarPointer());
        auto outputTempPlanePointer = (boolean_T *) (output3dEdgeData->GetScalarPointerForExtent(tempPlaneExtent));

        memcpy(outputTempPlanePointer, afterSubPointer, 640000 * sizeof(boolean_T));

        cout << i << "th" << endl;


//        writer->Print(cout);
    }

    vtkSmartPointer<vtkMetaImageWriter> writer =
            vtkSmartPointer<vtkMetaImageWriter>::New();

    writer->SetFileName("/Users/heliu/temp/node-centered/step4-3d/canny3d.mhd");
    writer->SetInputData(output3dEdgeData);
    writer->Write();

    return 0;
}
