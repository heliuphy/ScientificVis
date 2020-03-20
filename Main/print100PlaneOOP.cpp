//
// Created by 何柳 on 2020/3/20.
//


#include "ImageFill_types.h"
#include "rtwtypes.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkPNGWriter.h>
#include "HlwUtils.h"
#include <vector>
#include <vtkLookupTable.h>
#include <vtkImageMapToColors.h>

using std::calloc;
using std::cout;
using std::endl;
using std::vector;

struct ImageOriginSpacingExtent {
    double Origin[3];
    double Spacing[3];
    int Extent[6];
};

class Generate3DMaskData {
public:
    Generate3DMaskData(int zStart,
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

public:
    void printOriginalSlice() {
        for (int i = 0; i < zIndexes.size(); i++) {
            // Extract plane from input 3d image data
            tempPlaneInfo->Extent[4] = zIndexes[i];
            tempPlaneInfo->Extent[5] = zIndexes[i];
            tempPlanePointer = (float *) (dim3InputData->GetScalarPointerForExtent(tempPlaneInfo->Extent));

            auto tempFloat2dImagePointer = (float *) (tempFloat2dImage->GetScalarPointer());
            memcpy(tempFloat2dImagePointer, tempPlanePointer, 640000 * sizeof(float));

            vtkSmartPointer<vtkImageMapToColors> colorMap2 =
                vtkSmartPointer<vtkImageMapToColors>::New();
            colorMap2->SetLookupTable(this->colorTable);
            colorMap2->SetInputData(tempFloat2dImage);
            colorMap2->Update();

//            colorMap->SetInputData(tempFloat2dImage);
//            colorMap->Update();

            _filename = _file_path + "Original_" + std::to_string(zIndexes[i]) + ".png";

            writer->SetFileName(_filename.c_str());
//            writer->SetInputData(colorMap->GetOutput());
            writer->SetInputData(colorMap2->GetOutput());
            writer->Write();

            cout << "Original_" << zIndexes[i] << ".png" << "  has been written \n";
        }

    }

    void printCannySlice() {

        for (int i = 0; i < zIndexes.size(); i++) {
            // Extract plane from input 3d image data
            tempPlaneInfo->Extent[4] = zIndexes[i];
            tempPlaneInfo->Extent[5] = zIndexes[i];
            tempPlanePointer = (float *) (dim3InputData->GetScalarPointerForExtent(tempPlaneInfo->Extent));

            planeBoundaryDetection(tempPlanePointer,
                                   afterCannyImageData,
                                   afterFillImageData,
                                   afterSubImageData,
                                   CANNY_ONLY);

            auto multiply255DataPointer = (boolean_T *) (multiply255->GetScalarPointer());
            booleanTArrayMultiplyByK((boolean_T *) (afterCannyImageData->GetScalarPointer()), multiply255DataPointer,
                                     255,
                                     800, 800);

            _filename = _file_path + "Canny_" + std::to_string(zIndexes[i]) + ".png";

            writer->SetFileName(_filename.c_str());
            writer->SetInputData(multiply255);
            writer->Write();
//        writer->Print(cout);
            cout << "Canny_" << zIndexes[i] << ".png" << "  has been written \n";
        }
    }

    void printAfterSubSlice() {

        for (int i = 0; i < zIndexes.size(); i++) {
            // Extract plane from input 3d image data
            tempPlaneInfo->Extent[4] = zIndexes[i];
            tempPlaneInfo->Extent[5] = zIndexes[i];
            tempPlanePointer = (float *) (dim3InputData->GetScalarPointerForExtent(tempPlaneInfo->Extent));

            planeBoundaryDetection(tempPlanePointer,
                                   afterCannyImageData,
                                   afterFillImageData,
                                   afterSubImageData,
                                   CANNY_FILL_AND_SUB);

            auto multiply255DataPointer = (boolean_T *) (multiply255->GetScalarPointer());
            booleanTArrayMultiplyByK((boolean_T *) (afterSubImageData->GetScalarPointer()), multiply255DataPointer,
                                     255,
                                     800, 800);


            _filename = _file_path + "Sub_" + std::to_string(zIndexes[i]) + ".png";

            writer->SetFileName(_filename.c_str());
            writer->SetInputData(multiply255);
            writer->Write();
//        writer->Print(cout);
            cout << "Sub_" << zIndexes[i] << ".png" << "  has been written \n";
        }
    }

public:
    int getZStart() const {
        return zStart;
    }

    void setZStart(int zStart) {
        Generate3DMaskData::zStart = zStart;
    }

    int getZEnd() const {
        return zEnd;
    }

    void setZEnd(int zEnd) {
        Generate3DMaskData::zEnd = zEnd;
    }

    int getPlaneSpacing() const {
        return planeSpacing;
    }

    void setPlaneSpacing(int planeSpacing) {
        Generate3DMaskData::planeSpacing = planeSpacing;
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

    void setAfterCannyImageData(vtkImageData *_afterCannyImageData) {
        afterCannyImageData = _afterCannyImageData;
        afterCannyImageData->SetOrigin(input2dImageInfo->Origin);
        afterCannyImageData->SetExtent(input2dImageInfo->Extent);
        afterCannyImageData->SetSpacing(input2dImageInfo->Spacing);
        afterCannyImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
    }

    vtkImageData *getAfterFillImageData() const {
        return afterFillImageData;
    }

    void setAfterFillImageData(vtkImageData *_afterFillImageData) {
        afterFillImageData = _afterFillImageData;
        afterFillImageData->SetOrigin(input2dImageInfo->Origin);
        afterFillImageData->SetExtent(input2dImageInfo->Extent);
        afterFillImageData->SetSpacing(input2dImageInfo->Spacing);
        afterFillImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
    }

    vtkImageData *getAfterSubImageData() const {
        return afterSubImageData;
    }

    void setAfterSubImageData(vtkImageData *_afterSubImageData) {
        afterSubImageData = _afterSubImageData;
        afterSubImageData->SetOrigin(input2dImageInfo->Origin);
        afterSubImageData->SetExtent(input2dImageInfo->Extent);
        afterSubImageData->SetSpacing(input2dImageInfo->Spacing);
        afterSubImageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
    }

    const string &getFilePath() const {
        return _file_path;
    }

    void setFilePath(const string &filePath) {
        _file_path = filePath;
    }

    vtkImageData *getMultiply255() const {
        return multiply255;
    }

    void setMultiply255(vtkImageData *_multiply255) {
        Generate3DMaskData::multiply255 = _multiply255;
        multiply255->SetOrigin(input2dImageInfo->Origin);
        multiply255->SetExtent(input2dImageInfo->Extent);
        multiply255->SetSpacing(input2dImageInfo->Spacing);
        multiply255->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
    }

    vtkImageData *getTempFloat2DImage() const {
        return tempFloat2dImage;
    }

    void setTempFloat2DImage(vtkImageData *_tempFloat2DImage) {
        tempFloat2dImage = _tempFloat2DImage;
        tempFloat2dImage->SetOrigin(input2dImageInfo->Origin);
        tempFloat2dImage->SetExtent(input2dImageInfo->Extent);
        tempFloat2dImage->SetSpacing(input2dImageInfo->Spacing);
        tempFloat2dImage->AllocateScalars(VTK_FLOAT, 1);
    }

    vtkPNGWriter *getWriter() const {
        return writer;
    }

    void setWriter(vtkPNGWriter *_writer) {
        Generate3DMaskData::writer = _writer;
    }

    vtkLookupTable *getColorTable() const {
        return colorTable;
    }

    void setColorTable(vtkLookupTable *_colorTable) {
        colorTable = _colorTable;
        colorTable->SetRange(100000.0, 24212800.0);
        colorTable->SetHueRange(0.667, 0);
        colorTable->Build();
    }


private:
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
    ImageOriginSpacingExtent *input2dImageInfo;
    ImageOriginSpacingExtent *input3dImageInfo;
    ImageOriginSpacingExtent *tempPlaneInfo;
    vtkPNGWriter *writer;
    vtkLookupTable *colorTable;
};

int main() {
    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/volume800Meta.mhd");
    reader->Update();

    vtkSmartPointer<vtkMetaImageReader> planeReader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    planeReader->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/output/plane.mhd");
    planeReader->Update();

    vtkSmartPointer<vtkImageData> input3DImageData = reader->GetOutput();
    vtkSmartPointer<vtkImageData> planeImageData = planeReader->GetOutput();

    int zStart = 0;
    int zEnd = 20;
    int planeSpacing = 1;

    Generate3DMaskData printP(zStart,
                              zEnd,
                              planeSpacing,
                              planeReader->GetOutput(),
                              reader->GetOutput());

    vtkSmartPointer<vtkImageData> afterCannyImageData =
            vtkSmartPointer<vtkImageData>::New();
    printP.setAfterCannyImageData(afterCannyImageData);

    vtkSmartPointer<vtkImageData> afterFillImageData
            = vtkSmartPointer<vtkImageData>::New();
    printP.setAfterFillImageData(afterFillImageData);

    vtkSmartPointer<vtkImageData> afterSubImageData =
            vtkSmartPointer<vtkImageData>::New();
    printP.setAfterSubImageData(afterSubImageData);

    vtkSmartPointer<vtkImageData> multiply255 =
            vtkSmartPointer<vtkImageData>::New();
    printP.setMultiply255(multiply255);

    vtkSmartPointer<vtkImageData> tempFloat2dImage =
            vtkSmartPointer<vtkImageData>::New();
    printP.setTempFloat2DImage(tempFloat2dImage);

    vtkSmartPointer<vtkPNGWriter> writer =
            vtkSmartPointer<vtkPNGWriter>::New();
    printP.setWriter(writer);

    vtkSmartPointer<vtkLookupTable> colorTable =
            vtkSmartPointer<vtkLookupTable>::New();
    printP.setColorTable(colorTable);


    printP.setFilePath("/Users/heliu/temp/node-centered/step3-slice/OOPTest/");

    printP.printOriginalSlice();
    printP.printCannySlice();
    printP.printAfterSubSlice();
}
