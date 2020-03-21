//
// Created by 何柳 on 2020/3/15.
//

#include "HlwUtils.h"
#include <iostream>
#include <vtkType.h>
#include <vtkImageData.h>
#include "ImageFill_types.h"
#include "ImageFill.h"
#include "ImageFill_terminate.h"
#include "ImageFill_initialize.h"
#include "Canny.h"
#include "Canny_terminate.h"
#include "Canny_initialize.h"
#include "rtwtypes.h"

using std::string;
using std::cout;
using std::endl;


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

//    printArray<int>(planeExtent, 6, "planeExtent");
//    printArray<int>(horizontalLineExtent, 6, "horizonExtent");

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
    if (edgeNum < 4) {
        cout << "haven't found 4 edges " << endl;
    }

    // Determine the position of the four points relative
    // to the center point to determine whether it is on
    // the left or right half.

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

    if (edgeArray[0] < 399 && edgeArray[1] < 399 && edgeArray[2] < 399 && edgeArray[3] > 399) {
        *p1 = (pointIDs[0] + pointIDs[1]) / 2;
        *p2 = *p1;
    } else {
        *p1 = (pointIDs[0] + pointIDs[1]) / 2;
        *p2 = (pointIDs[2] + pointIDs[3]) / 2;
    }
//    printArray<int>(edgeArray, 4, "edgeArray");
//    printArray<vtkIdType>(pointIDs, 4, "pointIDs");

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

    // Always Do Canny_Z

    // Initialize
    Canny_initialize();


    // Canny_Z Edge Detection
    CannyAutoThres(_inputImageDataPointer, _afterCannyImagePointer);

    if (_doFill) {
        ImageFill_initialize();
        // Fill
        double *p1 = (double *) malloc(sizeof(double));
        double *p2 = (double *) malloc(sizeof(double));

        findPointIDToImfill(_afterCannyImageData, p1, p2);

        cout << "p1 and p2 " << endl;
        cout << *p1 << " " << *p2 << endl;

        if (*p1 == *p2) {
            ImageFillOnlyOnePoint(_afterCannyImagePointer, *p1, _afterCannyAndFillImagePointer);
        } else {
            ImageFill(_afterCannyImagePointer, *p1, *p2, _afterCannyAndFillImagePointer);
        }

        if (_doSub) {
            // 计算两图之差
            booleanTArraySub(_afterCannyAndFillImagePointer, _afterCannyImagePointer,
                             _afterSubImagePointer, 800, 800);
        }
        // Clean
        ImageFill_terminate();
    }

    // Clean
    Canny_terminate();

}


