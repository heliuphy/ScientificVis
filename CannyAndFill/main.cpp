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
#include "utils/HlwUtils.h"

#define CANNY_ONLY 0
#define CANNY_AND_FILL 1
#define CANNY_FILL_AND_SUB 2

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
planeBoundaryDetection(vtkImageData *_inputImageData,
                       vtkImageData *_afterCannyImageData,
                       vtkImageData *_afterCannyAndFillImageData,
                       vtkImageMathematics *_afterSub,
                       int _options) {
    bool _doCanny = false;
    bool _doFill = false;
    bool _doSub = false;


    auto _inputImagePointer = (float *) (_inputImageData->GetScalarPointer());
    auto _afterCannyImagePointer = (boolean_T *) (_afterCannyImageData->GetScalarPointer());
    auto _afterCannyAndFillImagePointer = (boolean_T *) (_afterCannyAndFillImageData->GetScalarPointer());

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
    CannyAutoThres(_inputImagePointer, _afterCannyImagePointer);

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
            _afterSub->SetInput1Data(_afterCannyAndFillImageData);
            _afterSub->SetInput2Data(_afterCannyImageData);
            _afterSub->SetOperationToSubtract();
            _afterSub->Update();
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

    vtkSmartPointer<vtkImageData> inputImageData = reader->GetOutput();

//    vtkSmartPointer<vtkImageData> outputImageData =
//            vtkSmartPointer<vtkImageData>::New();
//
//    outputImageData->SetOrigin(inputImageData->GetOrigin());
//    outputImageData->SetExtent(inputImageData->GetExtent());
//    outputImageData->SetSpacing(inputImageData->GetSpacing());
//    outputImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
//    auto outputImageDataPointer = (boolean_T *) (outputImageData->GetScalarPointer());

    vtkSmartPointer<vtkImageData> afterCannyImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterCannyImageData->SetOrigin(inputImageData->GetOrigin());
    afterCannyImageData->SetExtent(inputImageData->GetExtent());
    afterCannyImageData->SetSpacing(inputImageData->GetSpacing());
    afterCannyImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);


    vtkSmartPointer<vtkImageData> afterCannyAndFillImageData =
            vtkSmartPointer<vtkImageData>::New();
    afterCannyAndFillImageData->SetOrigin(inputImageData->GetOrigin());
    afterCannyAndFillImageData->SetExtent(inputImageData->GetExtent());
    afterCannyAndFillImageData->SetSpacing(inputImageData->GetSpacing());
    afterCannyAndFillImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);


    vtkSmartPointer<vtkImageMathematics> afterSub =
            vtkSmartPointer<vtkImageMathematics>::New();


    planeBoundaryDetection(inputImageData,
                           afterCannyImageData,
                           afterCannyAndFillImageData,
                           afterSub,
                           CANNY_FILL_AND_SUB);

    vtkSmartPointer<vtkImageMathematics> multiply255 =
        vtkSmartPointer<vtkImageMathematics>::New();
    multiply255->SetInput1Data(afterSub->GetOutput());
    multiply255->SetOperationToMultiplyByK();
    multiply255->SetConstantK(255);
    multiply255->Update();
//     Save file
//    vtkSmartPointer<vtkMetaImageWriter> writer =
//            vtkSmartPointer<vtkMetaImageWriter>::New();
//    writer->SetFileName(argv[2]);
//    writer->SetInputConnection(multiply255->GetOutputPort());
////    writer->SetInputData(afterSub->GetOutput());
//    writer->Write();

    vtkSmartPointer<vtkPNGWriter> writer =
        vtkSmartPointer<vtkPNGWriter>::New();
    writer->SetFileName(argv[2]);
    writer->SetInputConnection(multiply255->GetOutputPort());
    writer->Write();


    return 0;
}
