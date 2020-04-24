//
// Created by 何柳 on 2020/4/22.
//

#ifndef MYPROJ_SLICETYPEDETECTOR_H
#define MYPROJ_SLICETYPEDETECTOR_H

#include "hlwPlaneAlgorithms.h"

class SliceTypeDetector : public hlwPlaneAlgorithms {
public:
    SliceTypeDetector();

    ~SliceTypeDetector();

    void findHorizontalIntersectionPoints(vector<int> &pointArray);

    void findVerticalIntersectionPoints(vector<int> &pointArray);

    void findSlashIntersectionPoints(vector<int> &pointArray);

    void findBackslashIntersectionPoints(vector<int> &pointArray);

    void detectType();

    void run() override;

protected:
    int type = 0;

    vector<int> horizontalIntersections;
    vector<int> verticalIntersections;
    vector<int> slashIntersections;
    vector<int> backslashIntersections;
};


#endif //MYPROJ_SLICETYPEDETECTOR_H
