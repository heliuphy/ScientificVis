//
// Created by 何柳 on 2020/3/14.
//
#include "ImageFill_types.h"
#include "ImageFill.h"
#include "ImageFill_terminate.h"
#include "ImageFill_initialize.h"
#include "CannyAutoThres.h"
#include "CannyAutoThres_terminate.h"
#include "CannyAutoThres_initialize.h"
#include "rtwtypes.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkPNGWriter.h>
#include <vtkMetaImageWriter.h>
#include <vtkImageMathematics.h>
#include "HlwUtils.h"

#define CANNY_ONLY 0
#define CANNY_AND_FILL 1
#define CANNY_FILL_AND_SUB 2

void booleanTArraySub(const boolean_T *inputArray1,
                      const boolean_T *inputArray2,
                      boolean_T *outputArray,
                      int xSize, int ySize) {
    int squareSize = xSize * ySize;
    for (int i = 0; i < squareSize; i++) {
        outputArray[i] = inputArray1[i] - inputArray2[i];
    }
}

void booleanTArrayMultiplyByK(const boolean_T *inputArray,
                              boolean_T *outputArray,
                              int k,
                              int xSize, int ySize
) {
    int squareSize = xSize * ySize;
    for (int i = 0; i < squareSize; i++) {
        outputArray[i] = inputArray[i] * k;
    }
}

void findPointIDToImfill(vtkImageData *afterCannyImageData, double *p1, double *p2) {
    int planeExtent[6];
    afterCannyImageData->GetExtent(planeExtent);

    int horizontalLineExtent[6] = {0, 0, 0, 0, 0, 0};
    horizontalLineExtent[1] = planeExtent[1];
    horizontalLineExtent[2] = (planeExtent[3] - planeExtent[2]) / 2;
    horizontalLineExtent[3] = horizontalLineExtent[2];
    horizontalLineExtent[4] = planeExtent[4];
    horizontalLineExtent[5] = planeExtent[5];

    printArray<int>(planeExtent, 6, "planeExtent");
    printArray<int>(horizontalLineExtent, 6, "horizonExtent");

    int thisPoint = 0;
    // 遇到的边界编号,从左往右应该遇到8次
    int edgeNum = 0;
    int edgeArray[8] = {0};
    auto pixel = (unsigned char *) (afterCannyImageData->GetScalarPointerForExtent(horizontalLineExtent));
    for (int i = 0; i < horizontalLineExtent[1]; i++) {
        if (*pixel != 0) {
            edgeArray[edgeNum] = i;
            edgeNum++;
        }
        if (edgeNum == 4) {
            cout << "Have found 4 edges, Stop !" << endl;
            break;
        }
        pixel++;
    }
    int _y = horizontalLineExtent[2];
    int _z = horizontalLineExtent[4];
    int ijk[3] = {0};
    ijk[1] = _y;
    ijk[2] = _z;
    vtkIdType pointIDs[4] = {0};
    for (int i = 0; i < 4; i++) {
        ijk[0] = edgeArray[i];
        pointIDs[i] = afterCannyImageData->ComputePointId(ijk);
    }

    *p1 = (pointIDs[0] + pointIDs[1]) / 2;
    *p2 = (pointIDs[2] + pointIDs[3]) / 2;

    printArray<int>(edgeArray, 4, "edgeArray");
    printArray<vtkIdType>(pointIDs, 4, "pointIDs");

}

void
planeBoundaryDetection(float *_inputImageDataPointer,
                       vtkImageData *_afterCannyImageData,
                       vtkImageData *_afterCannyAndFillImageData,
                       vtkImageData *_afterSubImageData,
                       int _options) {
    bool _doCanny = false;
    bool _doFill = false;
    bool _doSub = false;


    auto _afterCannyImagePointer = (boolean_T *) (_afterCannyImageData->GetScalarPointer());
    auto _afterCannyAndFillImagePointer = (boolean_T *) (_afterCannyAndFillImageData->GetScalarPointer());
    auto _afterSubImagePointer = (boolean_T *) (_afterSubImageData->GetScalarPointer());

    switch (_options) {
        case CANNY_ONLY:
            _doCanny = true;
            break;
        case CANNY_AND_FILL:
            _doCanny = true;
            _doFill = true;
            break;
        case CANNY_FILL_AND_SUB:
            _doCanny = true;
            _doFill = true;
            _doSub = true;
            break;
        default:
            cout << "planeBoundaryDetection option err !" << endl;
            return;
    }

    // Always Do Canny

    // Initialize
    CannyAutoThres_initialize();


    // Canny Edge Detection
    CannyAutoThres(_inputImageDataPointer, _afterCannyImagePointer);

    if (_doFill) {
        ImageFill_initialize();
        // Fill
        double *p1 = (double *) malloc(sizeof(double));
        double *p2 = (double *) malloc(sizeof(double));

        findPointIDToImfill(_afterCannyImageData, p1, p2);

        cout << "p1 and p2 " << endl;
        cout << *p1 << " " << *p2 << endl;

        ImageFill(_afterCannyImagePointer, *p1, *p2, _afterCannyAndFillImagePointer);

        if (_doSub) {
            // 计算两图之差
            booleanTArraySub(_afterCannyAndFillImagePointer, _afterCannyImagePointer,
                             _afterSubImagePointer, 800, 800);
        }
        // Clean
        ImageFill_terminate();
    }

    // Clean
    CannyAutoThres_terminate();

}

int main(int argc, char **argv) {
    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    reader->Print(cout);

    vtkSmartPointer<vtkMetaImageReader> planeReader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    planeReader->SetFileName(argv[2]);
    planeReader->Update();
    planeReader->Print(cout);

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
    afterCannyImageData->Print(cout);


    vtkSmartPointer<vtkImageData> afterCannyAndFillImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterCannyAndFillImageData->SetOrigin(planeImageData->GetOrigin());
    afterCannyAndFillImageData->SetExtent(planeImageData->GetExtent());
    afterCannyAndFillImageData->SetSpacing(planeImageData->GetSpacing());
    afterCannyAndFillImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
    afterCannyAndFillImageData->Print(cout);

    vtkSmartPointer<vtkImageData> afterSubImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterSubImageData->SetOrigin(planeImageData->GetOrigin());
    afterSubImageData->SetExtent(planeImageData->GetExtent());
    afterSubImageData->SetSpacing(planeImageData->GetSpacing());
    afterSubImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
    afterSubImageData->Print(cout);

    auto afterSubDataPointer = (boolean_T *)(afterSubImageData->GetScalarPointer());


    vtkSmartPointer<vtkImageData> multiply255 =
            vtkSmartPointer<vtkImageData>::New();
    multiply255->SetOrigin(planeImageData->GetOrigin());
    multiply255->SetExtent(planeImageData->GetExtent());
    multiply255->SetSpacing(planeImageData->GetSpacing());
    multiply255->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
    multiply255->Print(cout);

    auto multiply255DataPointer = (boolean_T *)(multiply255->GetScalarPointer());

    vtkSmartPointer<vtkPNGWriter> writer =
            vtkSmartPointer<vtkPNGWriter>::New();

    int zIndexes[9] = {0, 49, 99, 149, 199, 249, 299, 349, 399};
//    , 449, 499, 549, 599, 649, 699, 749, 799
    for (int i = 0; i < 9; i++) {
        // Extract plane from input 3d image data
        tempPlaneExtent[4] = zIndexes[i];
        tempPlaneExtent[5] = zIndexes[i];
        tempPlanePointer = (float *) (input3DImageData->GetScalarPointerForExtent(tempPlaneExtent));

        planeBoundaryDetection(tempPlanePointer,
                               afterCannyImageData,
                               afterCannyAndFillImageData,
                               afterSubImageData,
                               CANNY_ONLY);

        booleanTArrayMultiplyByK((boolean_T *)(afterCannyImageData->GetScalarPointer()), multiply255DataPointer, 255, 800, 800);

        std::string _filename;
        _filename = "/Users/heliu/temp/node-centered/step3-3d/" + std::to_string(zIndexes[i]) + ".png";
        writer->SetFileName(_filename.c_str());
        writer->SetInputData(multiply255);
        writer->Write();
        writer->Print(cout);
        cout << i << ".png" << "  has been written \n";
    }


//     Save file
//    vtkSmartPointer<vtkMetaImageWriter> writer =
//            vtkSmartPointer<vtkMetaImageWriter>::New();
//    writer->SetFileName(argv[2]);
//    writer->SetInputConnection(multiply255->GetOutputPort());
////    writer->SetInputData(afterSub->GetOutput());
//    writer->Write();



    return 0;
}
