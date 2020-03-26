//
// Created by 何柳 on 2020/3/26.
//

#include "CircleDelete.h"

#include <utility>

void CircleDelete::deleteCircle() {
    auto inputPixel = (unsigned char *) (inputImageData->GetScalarPointer());
    auto outputPixel = (unsigned char *) (outputImageData->GetScalarPointer());

    if (elementSize == -1) {
        computeElementSize();
    }
    assert(elementSize >= 0);
    memcpy(outputPixel,inputPixel, elementSize * sizeof(unsigned char));

    for (auto i :circleVector) {
        outputPixel[i] = 0;
    }
}

void CircleDelete::run() {
    deleteCircle();
}

void CircleDelete::setDeleteCircle(vector<int> _deleteCircle) {
    circleVector = std::move(_deleteCircle);
}
