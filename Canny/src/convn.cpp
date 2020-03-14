//
// File: convn.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 12-Mar-2020 09:21:19
//

// Include Files
#include "rt_nonfinite.h"
#include "CannyAutoThres.h"
#include "convn.h"

// Function Definitions

//
// Arguments    : const float A[649600]
//                const float B[13]
//                float C[640000]
// Return Type  : void
//
void b_convn(const float A[649600], const float B[13], float C[640000]) {
    int j;
    int k;
    int aidx;
    int b_j;
    int cidx;
    int r;
    memset(&C[0], 0, 640000U * sizeof(float));
    for (j = 0; j < 13; j++) {
        if (j < 12) {
            k = 12 - j;
        } else {
            k = 0;
        }

        while (k <= 811 - j) {
            aidx = k * 800;
            if (j + k > 12) {
                b_j = (j + k) - 12;
            } else {
                b_j = 0;
            }

            cidx = b_j * 800;
            for (r = 0; r < 800; r++) {
                C[cidx] += B[j] * A[aidx];
                aidx++;
                cidx++;
            }

            k++;
        }
    }
}

//
// Arguments    : const float A[649600]
//                const float B[13]
//                float C[640000]
// Return Type  : void
//
void convn(const float A[649600], const float B[13], float C[640000]) {
    int k;
    int iC;
    int iA;
    int iB;
    int i;
    int firstRowA;
    int a_length;
    int cidx;
    int r;
    memset(&C[0], 0, 640000U * sizeof(float));
    for (k = 0; k < 800; k++) {
        iC = k * 800;
        iA = k * 812;
        iB = 0;
        for (i = 0; i < 13; i++) {
            if (i < 12) {
                firstRowA = 12 - i;
            } else {
                firstRowA = 0;
            }

            a_length = 812 - (i + firstRowA);
            firstRowA += iA;
            cidx = iC;
            for (r = 1; r <= a_length; r++) {
                C[cidx] += B[iB] * A[firstRowA];
                firstRowA++;
                cidx++;
            }

            iB++;
            if (i >= 12) {
                iC++;
            }
        }
    }
}

//
// File trailer for convn.cpp
//
// [EOF]
//
