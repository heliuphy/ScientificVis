//
// Created by 何柳 on 2020/3/7.
//

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <iostream>
#include <vtkMetaImageReader.h>
#include <vtkMetaImageWriter.h>
#include <vtkExtractVOI.h>

using std::cout;
using std::endl;

template<class T>
void printArray(T *array, int length) {
    for (int i = 0; i < length; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int deleteOuterCircleUp(vtkImageData *inputImage, int _extent[6]) {
    // up
    for (int i = _extent[0]; i <= _extent[1]; i++) {
        unsigned char *_left = nullptr, *_right = nullptr;
        for (int j = _extent[3]; j >= _extent[2]; j--) {
            auto _pixel = (unsigned char *) (inputImage->GetScalarPointer(i, j, 0));
            if (*_pixel == 255 && _left == nullptr) {
                _left = _pixel;
            } else if (*_pixel == 255 && _left != nullptr) {
                *_left = 0;
                break;
            } else {
                continue;
            }
        }
    }
    return 0;
}

int deleteOuterCircleDown(vtkImageData *inputImage, int _extent[6]) {
    // up
    for (int i = _extent[0]; i <= _extent[1]; i++) {
        unsigned char *_left = nullptr, *_right = nullptr;
        for (int j = _extent[2]; j <= _extent[3]; j++) {
            auto _pixel = (unsigned char *) (inputImage->GetScalarPointer(i, j, 0));
            if (*_pixel == 255 && _left == nullptr) {
                _left = _pixel;
            } else if (*_pixel == 255 && _left != nullptr) {
                *_left = 0;
                break;
            } else {
                continue;
            }
        }
    }
    return 0;
}

int deleteOuterCircleLeft(vtkImageData *inputImage, int _extent[6]) {
    // up
    for (int i = _extent[2]; i <= _extent[3]; i++) {
        unsigned char *_left = nullptr, *_right = nullptr;
        for (int j = _extent[0]; j <= _extent[1]; j++) {
            auto _pixel = (unsigned char *) (inputImage->GetScalarPointer(j, i, 0));
            if (*_pixel == 255 && _left == nullptr) {
                _left = _pixel;
            } else if (*_pixel == 255 && _left != nullptr) {
                *_left = 0;
                break;
            } else {
                continue;
            }
        }
    }
    return 0;
}

int deleteOuterCircleRight(vtkImageData *inputImage, int _extent[6]) {
    // up
    for (int i = _extent[2]; i <= _extent[3]; i++) {
        unsigned char *_left = nullptr, *_right = nullptr;
        for (int j = _extent[1]; j >= _extent[0]; j--) {
            auto _pixel = (unsigned char *) (inputImage->GetScalarPointer(j, i, 0));
            if (*_pixel == 255 && _left == nullptr) {
                _left = _pixel;
            } else if (*_pixel == 255 && _left != nullptr) {
                *_left = 0;
                break;
            } else {
                continue;
            }
        }
    }
    return 0;
}

int deleteOuterCircleLeftUp(vtkImageData *inputImage, int _extent[6]) {
    int deltaX = _extent[1] - _extent[0];
    int deltaY = _extent[3] - _extent[2];
    int shortestDelta = deltaX > deltaY ? deltaY : deltaX;
    unsigned char *_left = nullptr, *_right = nullptr;
    for (int i = _extent[1] - shortestDelta, j = _extent[3]; i <= _extent[1]; i++, j--) {
        auto _pixel = (unsigned char *) (inputImage->GetScalarPointer(i, j, 0));
        if (*_pixel == 255 && _left == nullptr) {
            _left = _pixel;
        } else if (*_pixel == 255 && _left != nullptr) {
            *_left = 0;
            break;
        } else {
            continue;
        }
    }
    return 0;
}

int deleteOuterCircleRightUp(vtkImageData *inputImage, int _extent[6]) {
    int deltaX = _extent[1] - _extent[0];
    int deltaY = _extent[3] - _extent[2];
    int shortestDelta = deltaX > deltaY ? deltaY : deltaX;
    unsigned char *_left = nullptr, *_right = nullptr;
    for (int i = _extent[1] - shortestDelta, j = _extent[3]; i <= _extent[1]; i++, j--) {
        auto _pixel = (unsigned char *) (inputImage->GetScalarPointer(i, j, 0));
        if (*_pixel == 255 && _left == nullptr) {
            _left = _pixel;
        } else if (*_pixel == 255 && _left != nullptr) {
            *_left = 0;
            break;
        } else {
            continue;
        }
    }
    return 0;
}

int main(int argc, char **argv) {

    /**
     * Step 1 read original meta image which contains the binary edge line
     */
    if (argc != 3) {
        std::cout << argv[0] << " " << " file 1   file2 " << endl;
        return EXIT_FAILURE;
    }
    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();

    // Get original binary image information
    int extent[6];
    double spacing[3];
    double origin[3];

    vtkImageData *originalImageData = reader->GetOutput();
    originalImageData->GetExtent(extent);
    originalImageData->GetSpacing(spacing);
    originalImageData->GetOrigin(origin);

    cout << "extent: ";
    printArray<int>(extent, 6);
    cout << "spacing: ";
    printArray<double>(spacing, 3);
    cout << "origin: ";
    printArray<double>(origin, 3);

    /**
     * Step 2 find the border of the outer circle,
     * and wrap it with a rectangle.
     */

    // Find the middle horizontal line
    int middleHorizontalLineExtent[6] = {extent[0], extent[1], extent[3] / 2, extent[3] / 2, extent[4], extent[5]};
    auto middleHorizontalLine = (unsigned char *) (originalImageData->GetScalarPointerForExtent(
            middleHorizontalLineExtent));
    int leftBorder = 0, rightBorder = 0;

    auto originalPixel = middleHorizontalLine;
    for (int i = 0; i < extent[1] + 1; i++) {
        if (*originalPixel == 255) {
            leftBorder = i;
            break;
        }
        originalPixel++;
    }

    originalPixel = middleHorizontalLine + extent[1];
    for (int i = extent[1]; i >= 0; i--) {
        if (*originalPixel == 255) {
            rightBorder = i;
            break;
        }
        originalPixel++;
    }

    // Find the middle vertical line
    int middleVerticalLineExtent[6] = {extent[1] / 2, extent[1] / 2, extent[2], extent[3], extent[4], extent[5]};
    auto middleVerticalLine = (unsigned char *) (originalImageData->GetScalarPointerForExtent(
            middleHorizontalLineExtent));
    int upBorder = 0, downBorder = 0;

    originalPixel = middleVerticalLine;
    for (int i = 0; i < extent[3] + 1; i++) {
        if (*originalPixel == 255) {
            downBorder = i;
            break;
        }
        originalPixel++;
    }

    originalPixel = middleVerticalLine + extent[3];
    for (int i = extent[3]; i >= 0; i--) {
        if (*originalPixel == 255) {
            upBorder = i;
            break;
        }
        originalPixel++;
    }

    cout << "up down left right border: " << endl;
    cout << (int) upBorder << " " << (int) downBorder << " " << (int) leftBorder << " " << (int) rightBorder << " "
         << endl;

    vtkSmartPointer<vtkExtractVOI> voi =
            vtkSmartPointer<vtkExtractVOI>::New();
    voi->SetInputConnection(reader->GetOutputPort());
    voi->SetVOI(leftBorder - 2, rightBorder + 2, downBorder - 2, upBorder + 2, extent[4], extent[5]);
    voi->Update();
    /**
     * The VOI is the smallest rectangle which can wrap the outer circle.
     */

    //For test only
//    vtkSmartPointer<vtkMetaImageWriter> writer =
//            vtkSmartPointer<vtkMetaImageWriter>::New();
//    writer->SetFileName(argv[2]);
//    writer->SetInputData(voi->GetOutput());
//    writer->Write();

    int VOIExtent[6];
    vtkImageData *VOIImageData = voi->GetOutput();
    VOIImageData->GetExtent(VOIExtent);
    cout << "VOI Extent: " << endl;
    printArray<int>(VOIExtent, 6);

    /**
     * Step 3 Test up region
     */

    int VOIStart = 195, VOIEnd = 603;
    int VOILength = VOIEnd - VOIStart + 1;
    int oneSix = VOILength / 6;
    int oneThree = VOILength / 3;
    int fiveSix = VOILength / 6 * 5;

//    int upExtent[6] = {VOIStart + oneSix, VOIEnd - oneSix, VOIEnd - oneThree, VOIEnd, 0, 0};
//    deleteOuterCircleUp(VOIImageData, upExtent);
//
//    int downExtent[6] = {VOIStart + oneSix, VOIEnd - oneSix, VOIStart, VOIStart + oneThree, 0, 0};
//    deleteOuterCircleDown(VOIImageData, downExtent);
//
//    int leftExtent[6] = {VOIStart, VOIStart + oneThree, VOIStart + oneSix, VOIEnd - oneSix, 0, 0};
//    deleteOuterCircleLeft(VOIImageData, leftExtent);
//
//    int rightExtent[6] = {VOIEnd - oneThree, VOIEnd, VOIStart + oneSix, VOIEnd - oneSix, 0, 0};
//    deleteOuterCircleRight(VOIImageData, rightExtent);
    int leftUpExtent[6] = {VOIStart, VOIStart + oneThree, VOIEnd - oneThree, VOIEnd, 0, 0};
    deleteOuterCircleLeftUp(VOIImageData, leftUpExtent);

    vtkSmartPointer<vtkMetaImageWriter> writer =
            vtkSmartPointer<vtkMetaImageWriter>::New();
    writer->SetFileName(argv[2]);
    writer->SetInputData(VOIImageData);
    writer->Write();

    return EXIT_SUCCESS;
}
