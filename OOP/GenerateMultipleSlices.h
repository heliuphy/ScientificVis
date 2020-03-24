//
// Created by 何柳 on 2020/3/23.
//

#ifndef MYPROJ_GENERATEMULTIPLESLICES_H
#define MYPROJ_GENERATEMULTIPLESLICES_H

#include "AlgoBase.h"

struct ImageOriginSpacingExtent;

class GenerateMultipleSlices : public AlgoBase {
public:
    GenerateMultipleSlices(int zStart, int zEnd, int planeSpacing, vtkImageData *input2DImageData,
                           vtkImageData *input3DImageData);

public:
    void generateSpecificPositionSlices(vector<int> &_positions);

    void getZeroOneNumOfSpecificPlane(vector<int> &_positions);

    void getZeroOneNumOfSpecificPlane(vector<int> &_positions, vector<int> &count1s);

    void findIndexOfSpecialPlanes(vector<int> &_indexes, const bool _useCache);

    void findIndexOfSpecialPlanes(vector<int> &_indexes, vector<int> &_count1s, const bool _useCache);
};

#endif //MYPROJ_GENERATEMULTIPLESLICES_H
