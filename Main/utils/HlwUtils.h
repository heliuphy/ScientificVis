//
// Created by 何柳 on 2020/3/15.
//

#ifndef MYPROJ_HLWUTILS_H
#define MYPROJ_HLWUTILS_H


#define CANNY_ONLY 0
#define CANNY_AND_FILL 1
#define CANNY_FILL_AND_SUB 2

#include <string>
#include <iostream>
#include <vtkType.h>
#include <vtkImageData.h>
#include "ImageFill_types.h"
#include "ImageFill.h"
#include "ImageFill_terminate.h"
#include "ImageFill_initialize.h"
#include "CannyAutoThres.h"
#include "CannyAutoThres_terminate.h"
#include "CannyAutoThres_initialize.h"
#include "rtwtypes.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkPNGWriter.h>
#include <vtkMetaImageWriter.h>
#include <vtkImageMathematics.h>

using std::string;
using std::cout;
using std::endl;

template<class T>
void printArray(T *array, int size, string arrayName) {
    cout << arrayName << " : " << endl;
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

template<class T>
void deepCopyArray(T *inputArray, T *outputArray, int size) {
    for (int i = 0; i < size; i++) {
        outputArray[i] = inputArray[i];
    }
}


void booleanTArraySub(const boolean_T *inputArray1,
                      const boolean_T *inputArray2,
                      boolean_T *outputArray,
                      int xSize, int ySize);

void booleanTArrayMultiplyByK(const boolean_T *inputArray,
                              boolean_T *outputArray,
                              int k,
                              int xSize, int ySize
);

void findPointIDToImfill(vtkImageData *afterCannyImageData, double *p1, double *p2);

void
planeBoundaryDetection(float *_inputImageDataPointer,
                       vtkImageData *_afterCannyImageData,
                       vtkImageData *_afterCannyAndFillImageData,
                       vtkImageData *_afterSubImageData,
                       int _options);


#endif //MYPROJ_HLWUTILS_H
