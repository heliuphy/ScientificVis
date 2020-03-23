//
// Created by 何柳 on 2020/3/21.
//

#include "AlgoBase.h"
#include "rt_nonfinite.h"
#include "Canny.h"
#include "Canny_terminate.h"
#include "Canny_emxAPI.h"
#include "Canny_initialize.h"
#include "ImageFill.h"
#include "ImageFill_emxAPI.h"
#include "ImageFill_emxutil.h"
#include "ImageFill_initialize.h"
#include "ImageFill_types.h"

struct ImageOriginSpacingExtent {
    double Origin[3];
    double Spacing[3];
    int Extent[6];
};

AlgoBase::AlgoBase(int zStart,
                   int zEnd,
                   int planeSpacing,
                   vtkImageData *_input2dImageData,
                   vtkImageData *_input3dImageData)
        :
        zStart(zStart), zEnd(zEnd), planeSpacing(planeSpacing) {

    emxInitArray_real32_T(&toCannyEmxArray, 2);
    emxInitArray_boolean_T(&afterCannyEmxArray, 2);
    emxInitArray_boolean_T(&afterFillEmxArray, 2);
    emxInit_real_T(&pointIDsToFillEmxArray, 1);

    if (_input3dImageData != nullptr) {
        dim3InputData = _input3dImageData;
        input3dImageInfo = new ImageOriginSpacingExtent();

        _input3dImageData->GetOrigin(input3dImageInfo->Origin);
        _input3dImageData->GetSpacing(input3dImageInfo->Spacing);
        _input3dImageData->GetExtent(input3dImageInfo->Extent);
    }

    dim2InputData = _input2dImageData;

    input2dImageInfo = new ImageOriginSpacingExtent();
    tempPlaneInfo = new ImageOriginSpacingExtent();

    _input2dImageData->GetOrigin(input2dImageInfo->Origin);
    _input2dImageData->GetSpacing(input2dImageInfo->Spacing);
    _input2dImageData->GetExtent(input2dImageInfo->Extent);

    _input2dImageData->GetOrigin(tempPlaneInfo->Origin);
    _input2dImageData->GetSpacing(tempPlaneInfo->Spacing);
    _input2dImageData->GetExtent(tempPlaneInfo->Extent);
//   --------

    for (int i = zStart; i <= zEnd; i += planeSpacing) {
        zIndexes.push_back(i);
    }
}


void AlgoBase::setAfterCannyImageData(vtkImageData *_afterCannyImageData) {
    afterCannyImageData = _afterCannyImageData;
    afterCannyImageData->SetOrigin(input2dImageInfo->Origin);
    afterCannyImageData->SetExtent(input2dImageInfo->Extent);
    afterCannyImageData->SetSpacing(input2dImageInfo->Spacing);
    afterCannyImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
}

void AlgoBase::setAfterFillImageData(vtkImageData *_afterFillImageData) {
    afterFillImageData = _afterFillImageData;
    afterFillImageData->SetOrigin(input2dImageInfo->Origin);
    afterFillImageData->SetExtent(input2dImageInfo->Extent);
    afterFillImageData->SetSpacing(input2dImageInfo->Spacing);
    afterFillImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
}

void AlgoBase::setAfterSubImageData(vtkImageData *_afterSubImageData) {
    afterSubImageData = _afterSubImageData;
    afterSubImageData->SetOrigin(input2dImageInfo->Origin);
    afterSubImageData->SetExtent(input2dImageInfo->Extent);
    afterSubImageData->SetSpacing(input2dImageInfo->Spacing);
    afterSubImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
}

void AlgoBase::setMultiply255(vtkImageData *_multiply255) {
    AlgoBase::multiply255 = _multiply255;
    multiply255->SetOrigin(input2dImageInfo->Origin);
    multiply255->SetExtent(input2dImageInfo->Extent);
    multiply255->SetSpacing(input2dImageInfo->Spacing);
    multiply255->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
}


void AlgoBase::setTempFloat2DImage(vtkImageData *_tempFloat2DImage) {
    tempFloat2dImage = _tempFloat2DImage;
    tempFloat2dImage->SetOrigin(input2dImageInfo->Origin);
    tempFloat2dImage->SetExtent(input2dImageInfo->Extent);
    tempFloat2dImage->SetSpacing(input2dImageInfo->Spacing);
    tempFloat2dImage->AllocateScalars(VTK_FLOAT, 1);
}

void AlgoBase::setColorTable(vtkLookupTable *_colorTable) {
    colorTable = _colorTable;
    colorTable->SetRange(100000.0, 24212800.0);
    colorTable->SetHueRange(0.667, 0);
    colorTable->Build();
}

void AlgoBase::setOutput3DEdgeData(vtkImageData *_output3DEdgeData) {
    output3dEdgeData = _output3DEdgeData;
    output3dEdgeData->SetExtent(input3dImageInfo->Extent);
    output3dEdgeData->SetOrigin(input3dImageInfo->Origin);
    output3dEdgeData->SetSpacing(input3dImageInfo->Spacing);
    output3dEdgeData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
}

void AlgoBase::setToCannyEmxArray(emxArray_real32_T *_toCannyEmxArray) {
    toCannyEmxArray = _toCannyEmxArray;
}

void AlgoBase::setAfterCannyEmxArray(emxArray_boolean_T *_afterCannyEmxArray) {
    afterCannyEmxArray = _afterCannyEmxArray;
}

void AlgoBase::cannyDetect() {

    float *toCannyDataPointer = (float *) (toCannyImageData->GetScalarPointer());

    int _dims[3] = {0, 0, 0};
    toCannyImageData->GetDimensions(_dims);

    std::sort(std::begin(_dims), std::end(_dims));
    // Set The biggest to size0
    int size0 = _dims[2];
    int size1 = _dims[1];
    assert(_dims[0] == 1);

    toCannyEmxArray->data = toCannyDataPointer;
    toCannyEmxArray->size[0] = size0;
    toCannyEmxArray->size[1] = size1;
    toCannyEmxArray->allocatedSize = toCannyEmxArray->size[0] * toCannyEmxArray->size[1];
    toCannyEmxArray->canFreeData = true;

    boolean_T *afterCannyDataPointer = (boolean_T *) (afterCannyImageData->GetScalarPointer());
    afterCannyEmxArray->data = afterCannyDataPointer;
    afterCannyEmxArray->size[0] = size0;
    afterCannyEmxArray->size[1] = size1;
    afterCannyEmxArray->allocatedSize = afterCannyEmxArray->size[0] * afterCannyEmxArray->size[1];
    afterCannyEmxArray->canFreeData = true;

    Canny(toCannyEmxArray, afterCannyEmxArray);
}

void AlgoBase::findPointIDToImfill(double *p1, double *p2) {

    int horizontalLineExtent[6] = {0, 0, 0, 0, 0, 0};
    horizontalLineExtent[1] = input2dImageInfo->Extent[1];
    horizontalLineExtent[2] = (input2dImageInfo->Extent[3] - input2dImageInfo->Extent[2]) / 2;
    horizontalLineExtent[3] = horizontalLineExtent[2];
    horizontalLineExtent[4] = input2dImageInfo->Extent[4];
    horizontalLineExtent[5] = input2dImageInfo->Extent[5];


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

void AlgoBase::findRealEdge() {

}

void AlgoBase::doImageFill(real_T _p1, real_T _p2) {

//    real_T array2Points[2] = {0};
//    real_T array1Points[1] = {0};
    real_T *array2Points = (real_T *) calloc(2, sizeof(real_T));
    real_T *array1Points = (real_T *) calloc(1, sizeof(real_T));


    if (_p1 == _p2) {
        // Fill one point
        pointIDsToFillEmxArray->data = array1Points;
        array1Points[0] = _p1;
        pointIDsToFillEmxArray->size[0] = 1;
        pointIDsToFillEmxArray->allocatedSize = pointIDsToFillEmxArray->size[0];
        pointIDsToFillEmxArray->canFreeData = true;

    } else {
        // Fill two points
        pointIDsToFillEmxArray->data = array2Points;
        array2Points[0] = _p1;
        array2Points[1] = _p2;
        pointIDsToFillEmxArray->size[0] = 2;
        pointIDsToFillEmxArray->allocatedSize = pointIDsToFillEmxArray->size[0];
        pointIDsToFillEmxArray->canFreeData = true;

    }

    boolean_T *_afterFillDataPointer = (boolean_T *) (afterFillImageData->GetScalarPointer());

    int _dims[3] = {0, 0, 0};
    afterFillImageData->GetDimensions(_dims);

    std::sort(std::begin(_dims), std::end(_dims));
    // Set The biggest to size0
    int size0 = _dims[2];
    int size1 = _dims[1];
    assert(_dims[0] == 1);

    afterFillEmxArray->data = _afterFillDataPointer;
    afterFillEmxArray->size[0] = size0;
    afterFillEmxArray->size[1] = size1;
    afterFillEmxArray->allocatedSize = afterFillEmxArray->size[0] * afterFillEmxArray->size[1];
    afterFillEmxArray->canFreeData = true;

    ImageFill(afterCannyEmxArray, pointIDsToFillEmxArray, afterFillEmxArray);

    free(array2Points);
    free(array1Points);
}

void AlgoBase::twoImagesSub(vtkImageData *_imageData1, vtkImageData *_imageData2, vtkImageData *_resultImageData) {


    int _dims[3];
    _imageData1->GetDimensions(_dims);
    int squareSize = _dims[0] * _dims[1] * _dims[2];

    boolean_T *inputArray1 = (boolean_T *) (_imageData1->GetScalarPointer());
    boolean_T *inputArray2 = (boolean_T *) (_imageData2->GetScalarPointer());
    boolean_T *outputArray = (boolean_T *) (_resultImageData->GetScalarPointer());

    for (int i = 0; i < squareSize; i++) {
        outputArray[i] = inputArray1[i] - inputArray2[i];
    }
}


void AlgoBase::booleanImageMultiplyByK(vtkImageData *_inputImageData, vtkImageData *_outputImageData, int k) {


    int _dims[3];
    _inputImageData->GetDimensions(_dims);

    boolean_T *inputArray = (boolean_T *) (_inputImageData->GetScalarPointer());
    boolean_T *outputArray = (boolean_T *) (_outputImageData->GetScalarPointer());

    int squareSize = _dims[0] * _dims[1] * _dims[2];

    for (int i = 0; i < squareSize; i++) {
        outputArray[i] = inputArray[i] * k;
    }
}

void AlgoBase::setToCannyImageData(vtkImageData *_toCannyImageData) {
    AlgoBase::toCannyImageData = _toCannyImageData;
}



