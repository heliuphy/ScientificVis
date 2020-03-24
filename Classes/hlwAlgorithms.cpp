//
// Created by 何柳 on 2020/3/23.
//

#include "hlwAlgorithms.h"

#include <vtkImageData.h>


hlwAlgorithms::hlwAlgorithms() {

}

hlwAlgorithms::~hlwAlgorithms() {

}

void hlwAlgorithms::setInputImageData(vtkImageData *_inputImageData) {
    inputImageData = _inputImageData;
}

void hlwAlgorithms::setOutputImageData(vtkImageData *_outputImageData) {
    outputImageData = _outputImageData;
}

vtkImageData *hlwAlgorithms::getInputImageData() {
    return inputImageData;
}

vtkImageData *hlwAlgorithms::getOutputImageData() {
    return outputImageData;
}



