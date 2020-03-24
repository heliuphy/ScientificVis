//
// Created by 何柳 on 2020/3/24.
//

#include "hlwImageSlice.h"

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkMetaImageWriter.h>
#include "ImageOriginSpacingExtent.h"

int main() {
    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/volume800Meta.mhd");
    reader->Update();

    vtkSmartPointer<vtkMetaImageReader> referenceReader =
        vtkSmartPointer<vtkMetaImageReader>::New();
    referenceReader->SetFileName("/Users/heliu/temp/node-centered/Step1Reslice/output/plane.mhd");
    referenceReader->Update();

    ImageOriginSpacingExtent referenceInfo;
    referenceInfo.setOrigin(referenceReader->GetOutput()->GetOrigin());
    referenceInfo.setSpacing(referenceReader->GetOutput()->GetSpacing());
    referenceInfo.setExtent(referenceReader->GetOutput()->GetExtent());
    referenceInfo.setDimension(referenceReader->GetOutput()->GetDimensions());

    vtkSmartPointer<vtkImageData> outputImageData =
            vtkSmartPointer<vtkImageData>::New();
    outputImageData->SetOrigin(referenceReader->GetOutput()->GetOrigin());
    outputImageData->SetSpacing(referenceReader->GetOutput()->GetSpacing());
    outputImageData->SetExtent(referenceReader->GetOutput()->GetExtent());
    outputImageData->AllocateScalars(VTK_FLOAT, 1);

    hlwImageSlice imageSlice;
    imageSlice.setInputImageData(reader->GetOutput());
    imageSlice.setOutputImageData(outputImageData);
    imageSlice.setSliceIndex(199);
    imageSlice.setReferencePlaneInfo(&referenceInfo);
    imageSlice.computeSlicePlaneInformation();
    imageSlice.run();

    vtkSmartPointer<vtkMetaImageWriter> writer =
            vtkSmartPointer<vtkMetaImageWriter>::New();
    writer->SetFileName("/Users/heliu/temp/node-centered/Test/slice-test.mhd");
    writer->SetInputData(outputImageData);
    writer->Write();
}


