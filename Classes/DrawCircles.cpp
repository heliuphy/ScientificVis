//
// Created by 何柳 on 2020/5/22.
//

#include "DrawCircles.h"

void DrawCircles::run() {
    // 先清空画布
    outputImageClear();
    drawCircles();
}

void DrawCircles::setCirclesToDraw(vector<int> _toDrawCircles) {
    circleVector = std::move(_toDrawCircles);
}

void DrawCircles::outputImageClear() {
    if (elementSize == -1) {
        computeElementSize();
    }
    auto outputPointer = (unsigned char *) (outputImageData->GetScalarPointer());

    memset(outputPointer, 0, elementSize * sizeof(unsigned char));
}

void DrawCircles::drawCircles() {
    auto outputPixel = (unsigned char *) (outputImageData->GetScalarPointer());

    if (elementSize == -1) {
        computeElementSize();
    }
    assert(elementSize >= 0);

    for (auto i :circleVector) {
        outputPixel[i] = 1;
    }
}

DrawCircles::DrawCircles() {

}

DrawCircles::~DrawCircles() {

}

void DrawCircles::copyInputToOutput() {
    auto inputPixel = (unsigned char *) (inputImageData->GetScalarPointer());
    auto outputPixel = (unsigned char *) (outputImageData->GetScalarPointer());

    if (elementSize == -1) {
        computeElementSize();
    }
    assert(elementSize >= 0);
    memcpy(outputPixel, inputPixel, elementSize * sizeof(unsigned char));
}

