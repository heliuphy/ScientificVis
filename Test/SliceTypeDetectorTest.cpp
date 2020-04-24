//
// Created by 何柳 on 2020/4/23.
//

#include <vector>
#include "SliceTypeDetector.h"

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkMetaImageWriter.h>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

int main() {
    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName("/Users/heliu/OneDrive/Data/node-centered/Step-1-Reslice/output/CannyAutoPlane.mhd");
    reader->Update();

    SliceTypeDetector sliceTypeDetector;
    sliceTypeDetector.setInputImageData(reader->GetOutput());

    vector<int> horizontalIntersectPoint;
    vector<int> verticalIntersectPoint;
    vector<int> slashIntersectPoint;
    vector<int> backSlashIntersectPoint;

    sliceTypeDetector.findHorizontalIntersectionPoints(horizontalIntersectPoint);
    sliceTypeDetector.findVerticalIntersectionPoints(verticalIntersectPoint);
    sliceTypeDetector.findSlashIntersectionPoints(slashIntersectPoint);
    sliceTypeDetector.findBackslashIntersectionPoints(backSlashIntersectPoint);

    vector<vector<int>> fourTypeIntersectPoints;
    fourTypeIntersectPoints.push_back(horizontalIntersectPoint);
    fourTypeIntersectPoints.push_back(verticalIntersectPoint);
    fourTypeIntersectPoints.push_back(slashIntersectPoint);
    fourTypeIntersectPoints.push_back(backSlashIntersectPoint);

    for (int i = 0; i < 4; i++) {
        int arraySize = fourTypeIntersectPoints[i].size();
        cout << "fourTypeIntersectPoint[" << i << "]" << endl;
        cout << "point num = " << arraySize << endl;
        for (int j = 0; j < arraySize; j++) {
            cout << fourTypeIntersectPoints[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}


