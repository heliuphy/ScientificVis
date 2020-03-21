//
// Created by 何柳 on 2020/3/21.
//

#include "AlgoBase.h"

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

    dim3InputData = _input3dImageData;
    dim2InputData = _input2dImageData;

    input3dImageInfo = new ImageOriginSpacingExtent();
    input2dImageInfo = new ImageOriginSpacingExtent();
    tempPlaneInfo = new ImageOriginSpacingExtent();

    _input3dImageData->GetOrigin(input3dImageInfo->Origin);
    _input3dImageData->GetSpacing(input3dImageInfo->Spacing);
    _input3dImageData->GetExtent(input3dImageInfo->Extent);

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




