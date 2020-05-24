//
// Created by 何柳 on 2020/5/22.
//

#ifndef MYPROJ_DRAWCIRCLES_H
#define MYPROJ_DRAWCIRCLES_H

#include "hlwPlaneAlgorithms.h"
#include <vector>

class DrawCircles : public hlwPlaneAlgorithms {

public:

    DrawCircles();

    ~DrawCircles();

    void run() override;

    void setCirclesToDraw(vector<int> _toDrawCircles);

    void outputImageClear();

    void copyInputToOutput();

protected:
    void drawCircles();

    vector<int> circleVector;
};


#endif //MYPROJ_DRAWCIRCLES_H
