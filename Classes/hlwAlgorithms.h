//
// Created by 何柳 on 2020/3/23.
//

#ifndef MYPROJ_HLWALGORITHMS_H
#define MYPROJ_HLWALGORITHMS_H

#include <vtkImageData.h>

class hlwAlgorithms {
public:

    hlwAlgorithms();

    ~hlwAlgorithms();

    void setInputImageData(vtkImageData *_inputImageData);

    void setOutputImageData(vtkImageData *_outputImageData);

    vtkImageData *getInputImageData();

    vtkImageData *getOutputImageData();

    virtual void run() = 0;

protected:
    vtkImageData *inputImageData;
    vtkImageData *outputImageData;
};


#endif //MYPROJ_HLWALGORITHMS_H
