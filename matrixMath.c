#include <stdlib.h>
#include <math.h>
#include "matrixMath.h"
#include <gsl/gsl_sf_bessel.h>

void matrixMultiply(double **A, double **B, double **C, int m, int n, int p) {
    // A is a m x n matrix
    // B is a n x p matrix
    // C is a m x p matrix
    int i, j, k;

    for (i = 0; i < m; i++) {
        for (j = 0; j < p; j++) {
            //C[i][j] = 0;
            for (k = 0; k < n; k++) {
                C[i][j] += (double)(A[i][k] * B[k][j]);
            }
        }
    }
}  

void getRotationMatrix(double angle, double **matrix) {

    matrix[0][0] = cos(angle);
    matrix[0][1] = -sin(angle);
    matrix[1][0] = sin(angle);
    matrix[1][1] = cos(angle);

    
}
