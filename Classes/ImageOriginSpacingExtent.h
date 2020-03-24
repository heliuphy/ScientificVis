//
// Created by 何柳 on 2020/3/24.
//

#ifndef MYPROJ_IMAGEORIGINSPACINGEXTENT_H
#define MYPROJ_IMAGEORIGINSPACINGEXTENT_H


struct ImageOriginSpacingExtent {

    ImageOriginSpacingExtent() {}

    void setOrigin(const double *origin) {
        for (int i = 0; i < 3; i++) {
            Origin[i] = origin[i];
        }
    }

    void setSpacing(const double *spacing) {
        for (int i = 0; i < 3; i++) {
            Spacing[i] = spacing[i];
        }
    }

    void setExtent(const int *extent) {
        for (int i = 0; i < 6; i++) {
            Extent[i] = extent[i];
        }
    }

    const double *getOrigin() const {
        return Origin;
    }

    const double *getSpacing() const {
        return Spacing;
    }

    const int *getExtent() const {
        return Extent;
    }

    const int *getDimension() const {
        return Dimension;
    }

    void getDimension(int *_dim) {
        for (int i = 0; i < 3; i++) {
            _dim[i] = Dimension[i];
        }
    }

    void setDimension(const int *_dim) {
        for (int i = 0; i < 3; i++) {
            Dimension[i] = _dim[i];
        }
    }

    double Origin[3]{};
    double Spacing[3]{};
    int Extent[6]{};
    int Dimension[3]{};

};

#endif //MYPROJ_IMAGEORIGINSPACINGEXTENT_H
