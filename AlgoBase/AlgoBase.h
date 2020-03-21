//
// Created by 何柳 on 2020/3/21.
//

#ifndef MYPROJ_ALGOBASE_H
#define MYPROJ_ALGOBASE_H


#include "ImageFill_types.h"
#include "rtwtypes.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkPNGWriter.h>
#include "HlwUtils.h"
#include "rtwtypes.h"
#include <vector>
#include <vtkLookupTable.h>
#include <vtkImageMapToColors.h>

using std::calloc;
using std::cout;
using std::endl;
using std::vector;

struct ImageOriginSpacingExtent;


class AlgoBase {
public:
    AlgoBase(int zStart,
             int zEnd,
             int planeSpacing,
             vtkImageData *_input2dImageData,
             vtkImageData *_input3dImageData);

public:
    int getZStart() const {
        return zStart;
    }

    void setZStart(int zStart) {
        AlgoBase::zStart = zStart;
    }

    int getZEnd() const {
        return zEnd;
    }

    void setZEnd(int zEnd) {
        AlgoBase::zEnd = zEnd;
    }

    int getPlaneSpacing() const {
        return planeSpacing;
    }

    void setPlaneSpacing(int planeSpacing) {
        AlgoBase::planeSpacing = planeSpacing;
    }

    vtkImageData *getDim3InputData() const {
        return dim3InputData;
    }

    void setDim3InputData(vtkMetaImageReader *_reader) {
        dim3InputData = _reader->GetOutput();
    }

    vtkImageData *getDim2InputData() const {
        return dim2InputData;
    }

    void setDim2InputData(vtkMetaImageReader *_reader) {
        dim2InputData = _reader->GetOutput();
    }

    vtkImageData *getAfterCannyImageData() const {
        return afterCannyImageData;
    }

    void setAfterCannyImageData(vtkImageData *_afterCannyImageData);

    vtkImageData *getAfterFillImageData() const {
        return afterFillImageData;
    }

    void setAfterFillImageData(vtkImageData *_afterFillImageData);

    vtkImageData *getAfterSubImageData() const {
        return afterSubImageData;
    }

    void setAfterSubImageData(vtkImageData *_afterSubImageData);

    const string &getFilePath() const {
        return _file_path;
    }

    void setFilePath(const string &filePath) {
        _file_path = filePath;
    }

    vtkImageData *getMultiply255() const {
        return multiply255;
    }

    void setMultiply255(vtkImageData *_multiply255);

    vtkImageData *getTempFloat2DImage() const {
        return tempFloat2dImage;
    }

    void setTempFloat2DImage(vtkImageData *_tempFloat2DImage);

    void setWriter(vtkMetaImageWriter *_writer) {
        AlgoBase::writer = _writer;
    }

    vtkLookupTable *getColorTable() const {
        return colorTable;
    }

    void setColorTable(vtkLookupTable *_colorTable);

    vtkImageData *getOutput3DEdgeData() const {
        return output3dEdgeData;
    }

    void setOutput3DEdgeData(vtkImageData *_output3DEdgeData);

protected:
    int zStart;
    int zEnd;
    int planeSpacing;
    float *tempPlanePointer;
    std::string _filename;
    std::string _file_path;
    vector<int> zIndexes;
    vtkImageData *dim3InputData;
    vtkImageData *dim2InputData;
    vtkImageData *afterCannyImageData;
    vtkImageData *afterFillImageData;
    vtkImageData *afterSubImageData;
    vtkImageData *multiply255;
    vtkImageData *tempFloat2dImage;
    vtkImageData *output3dEdgeData;
    ImageOriginSpacingExtent *input2dImageInfo;
    ImageOriginSpacingExtent *input3dImageInfo;
    ImageOriginSpacingExtent *tempPlaneInfo;
    vtkMetaImageWriter *writer;
    vtkLookupTable *colorTable;
};


#endif //MYPROJ_ALGOBASE_H
