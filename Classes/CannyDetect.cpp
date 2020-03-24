//
// Created by 何柳 on 2020/3/24.
//

#include "CannyDetect.h"
#include "ImageOriginSpacingExtent.h"
#include "rt_nonfinite.h"
#include "Canny.h"
#include "Canny_terminate.h"
#include "Canny_emxAPI.h"
#include "Canny_initialize.h"


CannyDetect::CannyDetect() {

    emxInitArray_real32_T(&inputEmxArray, 2);
    emxInitArray_boolean_T(&outputEmxArray, 2);
}

void CannyDetect::run() {

    auto *inputDataPointer = (float *) (inputImageData->GetScalarPointer());

    int _dims[3] = {0, 0, 0};
    inputImageData->GetDimensions(_dims);

    std::sort(std::begin(_dims), std::end(_dims));
    // Set The biggest to size0
    int size0 = _dims[2];
    int size1 = _dims[1];
    assert(_dims[0] == 1);

    inputEmxArray->data = inputDataPointer;
    inputEmxArray->size[0] = size0;
    inputEmxArray->size[1] = size1;
    inputEmxArray->allocatedSize = inputEmxArray->size[0] * inputEmxArray->size[1];
    inputEmxArray->canFreeData = true;

    auto *afterCannyDataPointer = (boolean_T *) (outputImageData->GetScalarPointer());
    outputEmxArray->data = afterCannyDataPointer;
    outputEmxArray->size[0] = size0;
    outputEmxArray->size[1] = size1;
    outputEmxArray->allocatedSize = outputEmxArray->size[0] * outputEmxArray->size[1];
    outputEmxArray->canFreeData = true;

    Canny(inputEmxArray, outputEmxArray);
}
