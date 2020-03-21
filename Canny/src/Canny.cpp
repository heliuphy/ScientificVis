//
// File: Canny.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 21-Mar-2020 11:39:34
//

// Include Files
#include "rt_nonfinite.h"
#include "Canny.h"
#include "Canny_emxutil.h"
#include "edge.h"
#include "imfilter.h"
#include "libmwgetnumcores.h"
#include "libmwtbbhist.h"

// Function Declarations
static float rt_hypotf_snf(float u0, float u1);

// Function Definitions

//
// Arguments    : float u0
//                float u1
// Return Type  : float
//
static float rt_hypotf_snf(float u0, float u1) {
    float y;
    float a;
    float b;
    a = std::abs(u0);
    b = std::abs(u1);
    if (a < b) {
        a /= b;
        y = b * std::sqrt(a * a + 1.0F);
    } else if (a > b) {
        b /= a;
        y = a * std::sqrt(b * b + 1.0F);
    } else if (rtIsNaNF(b)) {
        y = b;
    } else {
        y = a * 1.41421354F;
    }

    return y;
}

//
// CANNYAUTOTHRES Summary of this function goes here
//    Detailed explanation goes here
// Arguments    : const emxArray_real32_T *inputImage
//                emxArray_boolean_T *outputImage
// Return Type  : void
//
void Canny(const emxArray_real32_T *inputImage, emxArray_boolean_T *outputImage) {
    double derivGaussKernel[13];
    static const double dv0[13] = {0.00050975920363612861, 0.0025659736304223,
                                   0.014594040963812248, 0.049305200293708981, 0.09498179875488523,
                                   0.089159205155936727, 0.0, -0.089159205155936727, -0.09498179875488523,
                                   -0.049305200293708981, -0.014594040963812248, -0.0025659736304223,
                                   -0.00050975920363612861};

    int aidx;
    double pad[2];
    double numCores;
    static const double dv1[6] = {0.0020299751839417141, 0.010218281014351701,
                                  0.058116735860084041, 0.19634433732941295, 0.37823877042972093,
                                  0.35505190018248872};

    int k;
    int firstRowA;
    emxArray_real32_T *dx;
    emxArray_real32_T *a;
    emxArray_real32_T *dy;
    int iv0[2];
    boolean_T useParallel;
    int cEnd;
    int cEnd1;
    int ma;
    int na;
    int lastColB;
    float h[13];
    int lastRowB;
    int a_length;
    int n;
    int lastColA;
    float idx;
    int b_n;
    int iC;
    boolean_T exitg1;
    int iA;
    int iB;
    double counts[64];
    int i;
    boolean_T x[64];
    boolean_T rngFlag;
    int r;
    static const float fv0[13] = {3.48133581E-5F, 0.00054457254F, 0.00516676065F,
                                  0.0297326539F, 0.103777163F, 0.219696254F, 0.282095581F, 0.219696254F,
                                  0.103777163F, 0.0297326539F, 0.00516676065F, 0.00054457254F, 3.48133581E-5F
    };

    signed char ii_data[1];
    double highThreshTemp_data[1];
    double highThresh_data[1];
    int b_i;
    emxArray_boolean_T *b_outputImage;
    if ((inputImage->size[0] == 0) || (inputImage->size[1] == 0)) {
        for (aidx = 0; aidx < 2; aidx++) {
            pad[aidx] = inputImage->size[aidx];
        }

        aidx = outputImage->size[0] * outputImage->size[1];
        outputImage->size[0] = (int) pad[0];
        emxEnsureCapacity((emxArray__common *) outputImage, aidx, sizeof(boolean_T));
        aidx = outputImage->size[0] * outputImage->size[1];
        outputImage->size[1] = (int) pad[1];
        emxEnsureCapacity((emxArray__common *) outputImage, aidx, sizeof(boolean_T));
        firstRowA = (int) pad[0] * (int) pad[1];
        for (aidx = 0; aidx < firstRowA; aidx++) {
            outputImage->data[aidx] = false;
        }
    } else {
        memcpy(&derivGaussKernel[0], &dv0[0], 13U * sizeof(double));
        for (aidx = 0; aidx < 6; aidx++) {
            derivGaussKernel[aidx] = dv1[aidx];
        }

        numCores = derivGaussKernel[7];
        for (k = 0; k < 5; k++) {
            numCores += derivGaussKernel[k + 8];
        }

        numCores = std::abs(numCores);
        for (aidx = 0; aidx < 6; aidx++) {
            derivGaussKernel[7 + aidx] /= numCores;
        }

        emxInit_real32_T(&dx, 2);
        aidx = dx->size[0] * dx->size[1];
        dx->size[0] = inputImage->size[0];
        dx->size[1] = inputImage->size[1];
        emxEnsureCapacity((emxArray__common *) dx, aidx, sizeof(float));
        firstRowA = inputImage->size[0] * inputImage->size[1];
        for (aidx = 0; aidx < firstRowA; aidx++) {
            dx->data[aidx] = inputImage->data[aidx];
        }

        emxInit_real32_T(&a, 2);
        imfilter(dx);
        b_imfilter(dx, derivGaussKernel);
        pad[0] = 0.0;
        pad[1] = 6.0;
        padImage(inputImage, pad, a);
        for (k = 0; k < 2; k++) {
            numCores = ((double) a->size[k] - (1.0 + 12.0 * (double) k)) + 1.0;
            iv0[k] = (int) numCores;
        }

        emxInit_real32_T(&dy, 2);
        aidx = dy->size[0] * dy->size[1];
        dy->size[0] = iv0[0];
        dy->size[1] = iv0[1];
        emxEnsureCapacity((emxArray__common *) dy, aidx, sizeof(float));
        firstRowA = iv0[0] * iv0[1];
        for (aidx = 0; aidx < firstRowA; aidx++) {
            dy->data[aidx] = 0.0F;
        }

        if ((a->size[0] == 0) || ((iv0[0] == 0) || (iv0[1] == 0))) {
            useParallel = true;
        } else {
            useParallel = false;
        }

        if (!useParallel) {
            cEnd = a->size[1] - 1;
            cEnd1 = a->size[0];
            ma = a->size[0];
            na = a->size[1] - 1;
            if (13 <= a->size[1] - 1) {
                lastColB = 13;
            } else {
                lastColB = a->size[1];
            }

            if (1 <= a->size[0] - 1) {
                lastRowB = 1;
            } else {
                lastRowB = a->size[0];
            }

            for (n = 0; n < lastColB; n++) {
                if (n + na < cEnd) {
                    lastColA = na;
                } else {
                    lastColA = cEnd - n;
                }

                if (n < 12) {
                    k = 12 - n;
                } else {
                    k = 0;
                }

                while (k <= lastColA) {
                    if (n + k > 12) {
                        b_n = (n + k) - 12;
                    } else {
                        b_n = 0;
                    }

                    iC = b_n * cEnd1;
                    iA = k * ma;
                    iB = n;
                    i = 0;
                    while (i <= lastRowB - 1) {
                        if (ma <= cEnd1 - 1) {
                            a_length = ma;
                        } else {
                            a_length = cEnd1;
                        }

                        aidx = iA;
                        firstRowA = iC;
                        for (r = 1; r <= a_length; r++) {
                            dy->data[firstRowA] += fv0[iB] * a->data[aidx];
                            aidx++;
                            firstRowA++;
                        }

                        iB++;
                        iC++;
                        i = 1;
                    }

                    k++;
                }
            }
        }

        pad[0] = 6.0;
        pad[1] = 0.0;
        if (!((dy->size[0] == 0) || (dy->size[1] == 0))) {
            for (aidx = 0; aidx < 13; aidx++) {
                h[aidx] = (float) derivGaussKernel[aidx];
            }

            padImage(dy, pad, a);
            for (k = 0; k < 2; k++) {
                numCores = ((double) a->size[k] - (13.0 + -12.0 * (double) k)) + 1.0;
                iv0[k] = (int) numCores;
            }

            aidx = dy->size[0] * dy->size[1];
            dy->size[0] = iv0[0];
            dy->size[1] = iv0[1];
            emxEnsureCapacity((emxArray__common *) dy, aidx, sizeof(float));
            firstRowA = iv0[0] * iv0[1];
            for (aidx = 0; aidx < firstRowA; aidx++) {
                dy->data[aidx] = 0.0F;
            }

            if ((a->size[1] == 0) || ((iv0[0] == 0) || (iv0[1] == 0))) {
                useParallel = true;
            } else {
                useParallel = false;
            }

            if (!useParallel) {
                cEnd = a->size[1] - 1;
                cEnd1 = a->size[0];
                ma = a->size[0];
                na = a->size[1] - 1;
                if (1 <= a->size[1] - 1) {
                    lastColB = 1;
                } else {
                    lastColB = a->size[1];
                }

                if (13 <= a->size[0] - 1) {
                    lastRowB = 13;
                } else {
                    lastRowB = a->size[0];
                }

                n = 0;
                while (n <= lastColB - 1) {
                    if (na < cEnd) {
                        lastColA = na;
                    } else {
                        lastColA = cEnd;
                    }

                    for (k = 0; k <= lastColA; k++) {
                        if (k > 0) {
                            firstRowA = k;
                        } else {
                            firstRowA = 0;
                        }

                        iC = firstRowA * (cEnd1 - 12);
                        iA = k * ma;
                        iB = 0;
                        for (i = 0; i < lastRowB; i++) {
                            if (i < 12) {
                                firstRowA = 12 - i;
                            } else {
                                firstRowA = 0;
                            }

                            if (i + ma <= cEnd1 - 1) {
                                b_i = ma;
                            } else {
                                b_i = cEnd1 - i;
                            }

                            a_length = b_i - firstRowA;
                            aidx = iA + firstRowA;
                            firstRowA = iC;
                            for (r = 1; r <= a_length; r++) {
                                dy->data[firstRowA] += h[iB] * a->data[aidx];
                                aidx++;
                                firstRowA++;
                            }

                            iB++;
                            if (i >= 12) {
                                iC++;
                            }
                        }
                    }

                    n = 1;
                }
            }
        }

        if (dx->size[0] <= dy->size[0]) {
            firstRowA = dx->size[0];
        } else {
            firstRowA = dy->size[0];
        }

        if (dx->size[1] <= dy->size[1]) {
            a_length = dx->size[1];
        } else {
            a_length = dy->size[1];
        }

        aidx = a->size[0] * a->size[1];
        a->size[0] = firstRowA;
        a->size[1] = a_length;
        emxEnsureCapacity((emxArray__common *) a, aidx, sizeof(float));
        n = dx->size[0] * dx->size[1];
        for (k = 0; k + 1 <= n; k++) {
            a->data[k] = rt_hypotf_snf(dx->data[k], dy->data[k]);
        }

        firstRowA = 1;
        n = a->size[0] * a->size[1];
        idx = a->data[0];
        if (a->size[0] * a->size[1] > 1) {
            if (rtIsNaNF(a->data[0])) {
                a_length = 2;
                exitg1 = false;
                while ((!exitg1) && (a_length <= n)) {
                    firstRowA = a_length;
                    if (!rtIsNaNF(a->data[a_length - 1])) {
                        idx = a->data[a_length - 1];
                        exitg1 = true;
                    } else {
                        a_length++;
                    }
                }
            }

            if (firstRowA < a->size[0] * a->size[1]) {
                while (firstRowA + 1 <= n) {
                    if (a->data[firstRowA] > idx) {
                        idx = a->data[firstRowA];
                    }

                    firstRowA++;
                }
            }
        }

        if (idx > 0.0F) {
            aidx = a->size[0] * a->size[1];
            emxEnsureCapacity((emxArray__common *) a, aidx, sizeof(float));
            firstRowA = a->size[0];
            a_length = a->size[1];
            firstRowA *= a_length;
            for (aidx = 0; aidx < firstRowA; aidx++) {
                a->data[aidx] /= idx;
            }
        }

        if ((a->size[0] == 0) || (a->size[1] == 0)) {
            memset(&counts[0], 0, sizeof(double) << 6);
        } else {
            numCores = 1.0;
            getnumcores(&numCores);
            if ((a->size[0] * a->size[1] > 500000) && (numCores > 1.0)) {
                useParallel = true;
            } else {
                useParallel = false;
            }

            if (useParallel) {
                useParallel = false;
                rngFlag = false;
                tbbhist_real32_scaled(&a->data[0], (double) (a->size[0] * a->size[1]),
                                      (double) a->size[0], (double) (a->size[0] * a->size
                        [1]) / (double) a->size[0], counts, 64.0, 1.0, 64.0, &rngFlag,
                                      &useParallel);
            } else {
                memset(&counts[0], 0, sizeof(double) << 6);
                aidx = a->size[0] * a->size[1];
                for (i = 0; i < aidx; i++) {
                    if (rtIsNaNF(a->data[i])) {
                        idx = 0.0F;
                    } else {
                        idx = a->data[i] * 63.0F + 0.5F;
                    }

                    if (idx < 0.0F) {
                        counts[0]++;
                    } else if (idx > 63.0F) {
                        counts[63]++;
                    } else if (rtIsInfF(a->data[i])) {
                        counts[63]++;
                    } else {
                        counts[(int) idx]++;
                    }
                }
            }
        }

        for (k = 0; k < 63; k++) {
            counts[k + 1] += counts[k];
        }

        numCores = 0.7 * (double) a->size[0] * (double) a->size[1];
        for (aidx = 0; aidx < 64; aidx++) {
            x[aidx] = (counts[aidx] > numCores);
        }

        a_length = 0;
        n = 1;
        firstRowA = 1;
        exitg1 = false;
        while ((!exitg1) && (firstRowA < 65)) {
            if (x[firstRowA - 1]) {
                a_length = 1;
                ii_data[0] = (signed char) firstRowA;
                exitg1 = true;
            } else {
                firstRowA++;
            }
        }

        if (a_length == 0) {
            n = 0;
        }

        for (aidx = 0; aidx < n; aidx++) {
            highThreshTemp_data[aidx] = (double) ii_data[aidx] / 64.0;
        }

        if (n != 0) {
            highThresh_data[0] = highThreshTemp_data[0];
            highThreshTemp_data[0] *= 0.4;
        }

        aidx = outputImage->size[0] * outputImage->size[1];
        outputImage->size[0] = inputImage->size[0];
        outputImage->size[1] = inputImage->size[1];
        emxEnsureCapacity((emxArray__common *) outputImage, aidx, sizeof(boolean_T));
        firstRowA = inputImage->size[0] * inputImage->size[1];
        for (aidx = 0; aidx < firstRowA; aidx++) {
            outputImage->data[aidx] = false;
        }

        firstRowA = inputImage->size[0];
        a_length = inputImage->size[1];
        if (!((firstRowA == 1) || (a_length == 1))) {
            emxInit_boolean_T(&b_outputImage, 2);
            aidx = b_outputImage->size[0] * b_outputImage->size[1];
            b_outputImage->size[0] = outputImage->size[0];
            b_outputImage->size[1] = outputImage->size[1];
            emxEnsureCapacity((emxArray__common *) b_outputImage, aidx, sizeof
                    (boolean_T));
            firstRowA = outputImage->size[0] * outputImage->size[1];
            for (aidx = 0; aidx < firstRowA; aidx++) {
                b_outputImage->data[aidx] = outputImage->data[aidx];
            }

            thinAndThreshold(b_outputImage, dx, dy, a, highThreshTemp_data,
                             highThresh_data, outputImage);
            emxFree_boolean_T(&b_outputImage);
        }

        emxFree_real32_T(&a);
        emxFree_real32_T(&dy);
        emxFree_real32_T(&dx);
    }
}

//
// File trailer for Canny.cpp
//
// [EOF]
//
