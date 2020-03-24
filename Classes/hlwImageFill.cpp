//
// Created by 何柳 on 2020/3/24.
//

#include "hlwImageFill.h"

hlwImageFill::hlwImageFill() {

    emxInitArray_boolean_T(&inputEmxArray, 2);
    emxInitArray_boolean_T(&outputEmxArray, 2);
    emxInitArray_real_T(&pointIdArray, 1);
}

void hlwImageFill::setFillPoints(real_T *_points, int len) {

    if (len == 1) {

        pointIdArray->data = _points;
        pointIdArray->size[0] = 1;
        pointIdArray->allocatedSize = pointIdArray->size[0];
        pointIdArray->canFreeData = true;

    } else if (len == 2) {

        pointIdArray->data = _points;
        pointIdArray->size[0] = 2;
        pointIdArray->allocatedSize = pointIdArray->size[0];
        pointIdArray->canFreeData = true;
    } else {
        cout << "only support 1 point and 2 points " << endl;
    }
}

void hlwImageFill::run() {


    auto inputPointer = (boolean_T *) (inputImageData->GetScalarPointer());
    auto outputPointer = (boolean_T *) (outputImageData->GetScalarPointer());

    int _dims[3] = {0, 0, 0};
    inputImageData->GetDimensions(_dims);

    std::sort(std::begin(_dims), std::end(_dims));
    // Set The biggest to size0
    int size0 = _dims[2];
    int size1 = _dims[1];
    assert(_dims[0] == 1);

    inputEmxArray->data = inputPointer;
    inputEmxArray->size[0] = size0;
    inputEmxArray->size[1] = size1;
    inputEmxArray->allocatedSize = inputEmxArray->size[0] * inputEmxArray->size[1];
    inputEmxArray->canFreeData = true;

    outputEmxArray->data = outputPointer;
    outputEmxArray->size[0] = size0;
    outputEmxArray->size[1] = size1;
    outputEmxArray->allocatedSize = outputEmxArray->size[0] * outputEmxArray->size[1];
    outputEmxArray->canFreeData = true;

    ImageFill(inputEmxArray, pointIdArray, outputEmxArray);

}

void hlwImageFill::findPointIDToImfill(double *p1, double *p2) {

    int inputExtent[6];
    inputImageData->GetExtent(inputExtent);

    int horizontalLineExtent[6] = {0, 0, 0, 0, 0, 0};
    horizontalLineExtent[1] = inputExtent[1];
    horizontalLineExtent[2] = (inputExtent[3] - inputExtent[2]) / 2;
    horizontalLineExtent[3] = horizontalLineExtent[2];
    horizontalLineExtent[4] = inputExtent[4];
    horizontalLineExtent[5] = inputExtent[5];


    // 遇到的边界编号,从左往右应该遇到8次
    int edgeNum = 0;
    int edgeArray[8] = {0};
    auto pixel = (unsigned char *) (inputImageData->GetScalarPointerForExtent(horizontalLineExtent));
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
        pointIDs[i] = inputImageData->ComputePointId(ijk);
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

