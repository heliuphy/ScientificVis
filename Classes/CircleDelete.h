//
// Created by 何柳 on 2020/3/26.
//

#ifndef MYPROJ_CIRCLEDELETE_H
#define MYPROJ_CIRCLEDELETE_H

#include "hlwPlaneAlgorithms.h"
#include <vector>

using std::vector;

class CircleDelete : public hlwPlaneAlgorithms {
public:

    void run() override;

    void setDeleteCircle(vector<int> _deleteCircle);

protected:

    void deleteCircle();

    vector<int> circleVector;
};


#endif //MYPROJ_CIRCLEDELETE_H
