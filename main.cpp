#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <gsl/gsl_blas.h>
#include <unistd.h>

#include <math.h>
#include "render.hpp"
#include "matrixMath.h"

#define PI 3.14159265358979

using namespace std;

int SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BUFFER_LEN = 0;




int main(int argc, char* argv[])
{

	// get the terminal width and height
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	SCREEN_WIDTH = w.ws_col;
	SCREEN_HEIGHT = w.ws_row;
	// buffer for ascii image (basically just a big ol' array of characters to write to the screen.
	// (it may be better to use a 2d array or something for just one image, but I chose to do it this way
	// because it fits better with the project I'm using this for
	char screenBuffer[SCREEN_WIDTH * SCREEN_HEIGHT]; 
	char nextScreenBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
	SCREEN_BUFFER_LEN = (int)(sizeof(screenBuffer)/sizeof(screenBuffer[0]));

	//disable terminal cursor 
	// TODO needs to be fixed
	//printf("\e[?25l");

	double square[] = { 50, 50, 0,
					 50, 100, 0,
					 100, 100, 0,
					 100, 50, 0};

	//struct vec3 square[4];

	// square[0].x = 0; 
	// square[0].y = 0;
	// square[0].z = 0;

	// square[1].x = 0; 
	// square[1].y = 50;
	// square[0].z = 0;

	// square[2].x = 50; 
	// square[2].y = 50;
	// square[0].z = 0;

	// square[3].x = 50; 
	// square[3].y = 0;
	// square[0].z = 0;

	double angle = 0;
	// double **transformedPoint;
	// double **point, **rotationMatrix;

	// point = (double **) malloc(2 * sizeof(double *));
	// transformedPoint = (double **) malloc(2 * sizeof(double *));
	// rotationMatrix = (double **) malloc(2 * sizeof(double *));

	// for (int i = 0; i < 2; i++) {
    //     point[i] = (double *) malloc(2 * sizeof(double));
    //     rotationMatrix[i] = (double *) malloc(1 * sizeof(double));
    //     transformedPoint[i] = (double *) malloc(1 * sizeof(double));

    // }


	// getRotationMatrix(angle, rotationMatrix);

	// point[0][1] = 0;
	// point[0][0] = 50;

	// matrixMultiply(point, rotationMatrix, transformedPoint, 2, 2, 1);
	// printf("Product of the matrices:\n");
    // for (int i = 0; i < 2; i++) {
    //     for (int j = 0; j < 2; j++) {
    //         printf("%f ", transformedPoint[i][j]);
    //     }
    //     printf("\n");
    // }

	// for (int i = 0;i < 4; i++) {
		
	// 	point[0][0] = square[i].x;
	// 	point[1][0] = square[i].y;
	// 	matrixMultiply(point, rotationMatrix, transformedPoint, 2, 2, 1);
	// 	square[i].x = (int)transformedPoint[0][0];
	// 	square[i].y = (int)transformedPoint[0][0];
	// 	angle += 0.1;
    // }
	

	flushBuffer(screenBuffer);

	double rotationMatrixX[] = {cos(angle), 0, sin(angle),
								0, 1, 0,
								-sin(angle), 0, cos(angle)};

	double productMatrix[] = {0, 0, 0, 
							  0, 0, 0, 
							  0, 0, 0};

	gsl_matrix_view A = gsl_matrix_view_array(square, 4, 3);
	gsl_matrix_view B = gsl_matrix_view_array(rotationMatrixX, 3, 3);
	gsl_matrix_view C = gsl_matrix_view_array(productMatrix, 4, 3);


	gsl_blas_dgemm (CblasNoTrans, CblasNoTrans,
				1.0, &A.matrix, &B.matrix,
				0.0, &C.matrix);

	

 	while (true)
 	{
		
		// for (int i = 0;i < 4; i++) {
			
		// 	point[0][0] = square[i].x;
		// 	point[1][0] = square[i].y;
		// 	matrixMultiply(point, rotationMatrix, transformedPoint, 2, 2, 1);
		// 	square[i].x = (int)transformedPoint[0][0];
		// 	square[i].y = (int)transformedPoint[1][0];
		// 	//printf("%d %d | ", square[i].x, square[i].y);

		// 	angle += 0.1;
		// }
		angle += 0.1;
		double square[] = { -15, -15, 0,
					 -15, 15, 0,
					 15, 15, 0,
					 15, -15, 0};
		double rotationMatrixY[] = {cos(angle), -sin(angle), 0,
								    sin(angle), cos(angle), 0,
								    0, 0, 1};
		double productMatrix[] = {0, 0, 0, 
							  0, 0, 0, 
							  0, 0, 0};

		gsl_matrix_view A = gsl_matrix_view_array(square, 4, 3);
		gsl_matrix_view C = gsl_matrix_view_array(productMatrix, 4, 3);
		gsl_matrix_view B = gsl_matrix_view_array(rotationMatrixY, 3, 3);

		gsl_blas_dgemm (CblasNoTrans, CblasNoTrans,
					1.0, &A.matrix, &B.matrix,
					0.0, &C.matrix);

		for (int i = 0; i < 12; i+=3) {
			//printf("%d, %d, %d\n", (int)productMatrix[i], (int)productMatrix[i+1], (int)productMatrix[i+3]);
			pixel(nextScreenBuffer, (int)productMatrix[i] + 40, (int)productMatrix[i+1] + 30, 255);
		}
			//		sleep(1);


		drawScreen(screenBuffer, nextScreenBuffer);
		flushBuffer(nextScreenBuffer);
		

		
 	}

	printf("\e[?25h");

 	return 0;

}
