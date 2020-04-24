//
// Created by 何柳 on 2020/3/26.
//

#ifndef MYPROJ_AREADELETE_H
#define MYPROJ_AREADELETE_H

#include "hlwPlaneAlgorithms.h"
#include <vector>

using std::vector;

class AreaDelete : public hlwPlaneAlgorithms {
public:

    void addToDeleteArea(int _pointID);

    int getNumOfAreaToDelete();

    void run() override;

protected:

    void deleteArea();

    vector<int> areaVector;

    int numOfAreaToDelete = 0;
};


#endif //
