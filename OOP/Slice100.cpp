//
// Created by 何柳 on 2020/3/21.
//

#include "Slice100.h"

struct ImageOriginSpacingExtent {
    double Origin[3];
    double Spacing[3];
    int Extent[6];
};

Slice100::Slice100(int zStart, int zEnd, int planeSpacing, vtkImageData *_input2dImageData,
                   vtkImageData *_input3dImageData) : AlgoBase(zStart, zEnd, planeSpacing, _input2dImageData,
                                                               _input3dImageData) {}

void Slice100::printOriginalSlice() {
    for (int i = 0; i < zIndexes.size(); i++) {
        // Extract plane from input 3d image data
        tempPlaneInfo->Extent[4] = zIndexes[i];
        tempPlaneInfo->Extent[5] = zIndexes[i];
        tempPlanePointer = (float *) (dim3InputData->GetScalarPointerForExtent(tempPlaneInfo->Extent));

        auto tempFloat2dImagePointer = (float *) (tempFloat2dImage->GetScalarPointer());
        memcpy(tempFloat2dImagePointer, tempPlanePointer, 640000 * sizeof(float));

        vtkSmartPointer <vtkImageMapToColors> colorMap2 =
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

void Slice100::printCannySlice() {

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

void Slice100::printAfterSubSlice() {

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

