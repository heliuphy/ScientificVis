//
// Created by 何柳 on 2020/3/24.
//

#ifndef MYPROJ_HLWIMAGESLICE_H
#define MYPROJ_HLWIMAGESLICE_H

#include "hlwVolumeAlgorithms.h"
#include "hlwPlaneAlgorithms.h"
#include "ImageOriginSpacingExtent.h"

class hlwImageSlice : public hlwVolumeAlgorithms {
public:

    hlwImageSlice();
    ~hlwImageSlice() override;

    void run() override;

    void setSliceIndex(int _index);

    void computeSlicePlaneInformation();

    void setReferencePlaneInfo(ImageOriginSpacingExtent *_referencePlaneInfo);

    void getSliceExtent(int* _extent);

protected:
    int sliceIndex;
    ImageOriginSpacingExtent *sliceInfo;
    ImageOriginSpacingExtent *referencePlaneInfo;

};


#endif //MYPROJ_HLWIMAGESLICE_H
