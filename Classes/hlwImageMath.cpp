//
// Created by 何柳 on 2020/3/24.
//

#include "hlwImageMath.h"


hlwImageMath::hlwImageMath() {

}

void hlwImageMath::setInputImageData2(vtkImageData *_inputImageData2) {
    inputImageData2 = _inputImageData2;
}

void hlwImageMath::setOperatorToSub() {
    oper = HLW_SUB;
}

void hlwImageMath::setOperatorToMultiplyK(int _k) {
    oper = HLW_MULTI_K;
    k = _k;
}

void hlwImageMath::run() {
    switch (oper) {
        case HLW_SUB:
            subTwoUnCharImageArray();
            break;
        case HLW_MULTI_K:
            array1MultiplyByK();
            break;
        default:
            cout << "error ! only support sub and multi K" << endl;
            break;
    }
}

void hlwImageMath::array1MultiplyByK() {

    int _dims[3];
    inputImageData->GetDimensions(_dims);

    auto inputArray = (unsigned char * )(inputImageData->GetScalarPointer());
    auto outputArray = (unsigned char * )(outputImageData->GetScalarPointer());

    int squareSize = _dims[0] * _dims[1] * _dims[2];

    for (int i = 0; i < squareSize; i++) {
        outputArray[i] = inputArray[i] * k;
    }
}

void hlwImageMath::subTwoUnCharImageArray() {

    int _dims[3];
    inputImageData->GetDimensions(_dims);
    int squareSize = _dims[0] * _dims[1] * _dims[2];

    auto inputArray1 = (unsigned char *) (inputImageData->GetScalarPointer());
    auto inputArray2 = (unsigned char *) (inputImageData2->GetScalarPointer());
    auto outputArray = (unsigned char *) (outputImageData->GetScalarPointer());

    for (int i = 0; i < squareSize; i++) {
        outputArray[i] = inputArray1[i] - inputArray2[i];
    }
}
