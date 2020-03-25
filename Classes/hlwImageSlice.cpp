//
// Created by 何柳 on 2020/3/24.
//

#include "hlwImageSlice.h"

void hlwImageSlice::run() {
    // Extract plane from input 3d image data
    auto slicePlanePointer = (float *) (inputImageData->GetScalarPointerForExtent(sliceInfo->Extent));

    int _dims[3];
    referencePlaneInfo->getDimension(_dims);
    std::sort(std::begin(_dims), std::end(_dims));
    assert(_dims[0] == 1);

    int _n = _dims[1] * _dims[2];

    auto outputImagePointer = (float *) (outputImageData->GetScalarPointer());
    memcpy(outputImagePointer, slicePlanePointer, _n * sizeof(float));

}

void hlwImageSlice::setSliceIndex(int _index) {
    sliceIndex = _index;
}

void hlwImageSlice::computeSlicePlaneInformation() {

    sliceInfo->setOrigin(referencePlaneInfo->getOrigin());
    sliceInfo->setSpacing(referencePlaneInfo->getSpacing());
    sliceInfo->setExtent(referencePlaneInfo->getExtent());

    sliceInfo->Extent[4] = sliceIndex;
    sliceInfo->Extent[5] = sliceIndex;

}

void hlwImageSlice::setReferencePlaneInfo(ImageOriginSpacingExtent *_referencePlaneInfo) {
    hlwImageSlice::referencePlaneInfo = _referencePlaneInfo;
}

hlwImageSlice::hlwImageSlice() {
    sliceInfo = new ImageOriginSpacingExtent;
}

hlwImageSlice::~hlwImageSlice() {
    delete sliceInfo;
}

void hlwImageSlice::getSliceExtent(int *_extent) {
    for (int i = 0; i < 6; i++) {
        _extent[i] = sliceInfo->Extent[i];
    }
}
