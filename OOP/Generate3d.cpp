//
// Created by 何柳 on 2020/3/21.
//

#include "Generate3d.h"

struct ImageOriginSpacingExtent {
    double Origin[3];
    double Spacing[3];
    int Extent[6];
};

Generate3d::Generate3d(int zStart, int zEnd, int planeSpacing, vtkImageData *_input2dImageData,
                       vtkImageData *_input3dImageData) : AlgoBase(zStart, zEnd, planeSpacing, _input2dImageData,
                                                                   _input3dImageData) {}

void Generate3d::generate3D() {

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

        auto afterSubPointer = (boolean_T *) (afterSubImageData->GetScalarPointer());
        auto outputTempPlanePointer = (boolean_T *) (output3dEdgeData->GetScalarPointerForExtent(
                tempPlaneInfo->Extent));

        memcpy(outputTempPlanePointer, afterSubPointer, 640000 * sizeof(boolean_T));

        cout << i << "th" << endl;
    }

    _filename = _file_path + "Mask3D.mhd";

    writer->SetFileName(_filename.c_str());
    writer->SetInputData(output3dEdgeData);
    writer->Write();
}


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
    int zEnd = 399;
    int planeSpacing = 1;

    Generate3d generate3DMaskData(zStart,
                                  zEnd,
                                  planeSpacing,
                                  planeReader->GetOutput(),
                                  reader->GetOutput());

    vtkSmartPointer<vtkImageData> afterCannyImageData =
            vtkSmartPointer<vtkImageData>::New();
    generate3DMaskData.setAfterCannyImageData(afterCannyImageData);

    vtkSmartPointer<vtkImageData> afterFillImageData
            = vtkSmartPointer<vtkImageData>::New();
    generate3DMaskData.setAfterFillImageData(afterFillImageData);

    vtkSmartPointer<vtkImageData> afterSubImageData =
            vtkSmartPointer<vtkImageData>::New();
    generate3DMaskData.setAfterSubImageData(afterSubImageData);

    vtkSmartPointer<vtkImageData> multiply255 =
            vtkSmartPointer<vtkImageData>::New();
    generate3DMaskData.setMultiply255(multiply255);

    vtkSmartPointer<vtkImageData> tempFloat2dImage =
            vtkSmartPointer<vtkImageData>::New();
    generate3DMaskData.setTempFloat2DImage(tempFloat2dImage);

    vtkSmartPointer<vtkMetaImageWriter> writer =
            vtkSmartPointer<vtkMetaImageWriter>::New();
    generate3DMaskData.setWriter(writer);

    vtkSmartPointer<vtkLookupTable> colorTable =
            vtkSmartPointer<vtkLookupTable>::New();
    generate3DMaskData.setColorTable(colorTable);


    vtkSmartPointer<vtkImageData> output3dEdgeData =
            vtkSmartPointer<vtkImageData>::New();
    generate3DMaskData.setOutput3DEdgeData(output3dEdgeData);

    generate3DMaskData.setFilePath("/Users/heliu/temp/node-centered/step3-slice/OOPTest/");

    generate3DMaskData.generate3D();
}
