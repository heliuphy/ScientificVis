//
// Created by 何柳 on 2020/3/7.
//
#include <iostream>
#include <vtkSmartPointer.h>
#include <vtkMetaImageReader.h>
#include <vtkImageData.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << argv[0] << "  filename.mhd" << endl;
        return EXIT_FAILURE;
    }

    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();

    int rectXMin = 180, rectXMax = 220;
    int rectYMin = 380, rectYMax = 420;

    int rectExtent[6] = {rectXMin, rectXMax, rectYMin, rectYMax, 0, 0};
    int rectXLen = rectXMax - rectXMin + 1;
    int rectYLen = rectYMax - rectYMin + 1;


    int lineXMin = 0, lineXMax = 799;
    int lineYMin = 400, lineYMax = 400;

    int lineExtent[6] = {lineXMin, lineXMax, lineYMin, lineYMax, 0, 0};
    int lineXLen = lineXMax - lineXMin + 1;
    int lineYLen = lineYMax - lineYMin + 1;

    // find the first point where value is 255

    vtkImageData *inputImageData = reader->GetOutput();
    auto linePointer = (unsigned char *) (inputImageData->GetScalarPointerForExtent(lineExtent));
    int minXValueNonZero = 0;
    for (int i = 0; i < lineXMax + 1; i++) {
//        auto pixelVal = (unsigned char *) ()
        if ()
    }

    auto rectPointer = (unsigned char *) (inputImageData->GetScalarPointerForExtent(rectExtent));

    for (int i = rectXMin; i < rectXMax + 1; i++) {
        for (int j = rectYMin; j < rectYMax + 1; j++) {
            if (*rectPointer == 0) {
                cout << (int) (*rectPointer) << "   ";
            } else {
                cout << (int) (*rectPointer) << " ";
            }
            rectPointer++;
        }
        cout << endl;
    }


    return EXIT_SUCCESS;
}
