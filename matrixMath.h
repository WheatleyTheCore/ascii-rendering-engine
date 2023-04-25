#ifndef MATRIXMATH_H
#define MATRIXMATH_H 1

void matrixMultiply(double **A, double **B, double **C, int m, int n, int p);

void getRotationMatrix(double angle, double **matrix);

#endif