#include <iostream>
#include <stdio.h>
#include <sys/ioctl.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <numeric>
#include <math.h>

using namespace std;

int SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BUFFER_LEN = 0;

// from lightest to darkest (if dark background and light text)
char brightnessChars[] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.                         ";

// map function for mapping number from one range to another
long mapValue(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// draw a "pixel" on the screen (top left is 0, 0)
void pixel(char* screenBuffer, int x, int y, int brightness) {
	int brightnessCharIndex = mapValue(brightness, 0, 255, sizeof(brightnessChars)/sizeof(brightnessChars[0]), 0);
	//printf("BrightnessIndex: %d\n", brightnessCharIndex);
	char pixelChar = brightnessChars[brightnessCharIndex]; //the character to draw to the screen

	long pixelIndex = SCREEN_WIDTH * y + y + x; //total lines above plus new lines plux the x value
	//printf("Pixel index: %ld", pixelIndex);
	screenBuffer[pixelIndex] = pixelChar;

}

void line(char* screenBuffer, int x1, int y1, int x2, int y2, int brightness) {
	int dx = x2 - x1;
	int dy = y2 - y1;

	int length = (int)sqrt(dx * dx + dy * dy);
	float angle = atan2(dy, dx);
	// printf("width: %d, height: %d, length %d, angle %f, dx %d, dy %d", SCREEN_WIDTH, SCREEN_HEIGHT, length, angle, dx, dy);


	for (int i = 0; i < length; i++) {
		pixel(screenBuffer, x1 + (int)(cos(angle) * i), y1 + (int)(sin(angle) * i), brightness);
	}
}

// empty screen buffer (make it all ' ')
void flushBuffer(char* screenBuffer) {      
	int screenBufferIndex = 0;
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			screenBuffer[screenBufferIndex] = ' ';
			screenBufferIndex++;
		}

		// add new line characters for every row except for the last one
		if (i < (SCREEN_HEIGHT - 1)) {
			screenBuffer[screenBufferIndex] = '\n';
			screenBufferIndex++;
		}
	}
	system("clear");
	sleep(0.01);
}

void drawScreen(char* screenBuffer) {
	for (int i = 0; i < SCREEN_BUFFER_LEN; i++) {
		printf("%c", screenBuffer[i]);
	}
}

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
	char screenBuffer[SCREEN_WIDTH * SCREEN_HEIGHT + SCREEN_HEIGHT - 1]; 
	char nextScreenBuffer[SCREEN_WIDTH * SCREEN_HEIGHT + SCREEN_HEIGHT - 1];
	SCREEN_BUFFER_LEN = (int)(sizeof(screenBuffer)/sizeof(screenBuffer[0]));

	//disable terminal cursor 
	// TODO needs to be fixed
	printf("\e[?25l");



	// print out dimensions of screen
    // printf ("width %d\n", SCREEN_WIDTH);
	// printf ("height %d\n", SCREEN_HEIGHT);
	// printf("screen buffer length: %d\n", SCREEN_BUFFER_LEN);


	//sleep(1);

	//drawScreen(screenBuffer);
	flushBuffer(screenBuffer);
	flushBuffer(nextScreenBuffer);

 	while (true)
 	{
		
		// for (int h = 0; h < SCREEN_HEIGHT; h++){
		// 	for (int i = 0; i < SCREEN_WIDTH; i++) {
		// 		flushBuffer(screenBuffer);
		// 		pixel(screenBuffer, i, h, 255);
		// 		drawScreen(screenBuffer);
		// 		sleep(0.05);
		// 	}			
		// }
		
		line(nextScreenBuffer, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 255);
		drawScreen(screenBuffer);
		sleep(0.5);
		// convert the brightness values to corresponding character for each pixel, and add to the screenBuffer
		// int screenBufferIndex = 0;
		// for (int i = 0; i < frame.rows; i++) {
		// 	for (int j = 0; j < frame.cols; j++) {
		// 		int pixelValue = (int)frame.at<uchar>(i,j);
		// 		int brightnessCharIndex = mapValue(pixelValue, 0, 255, (int)(sizeof(brightnessChars)/sizeof(brightnessChars[0])), 0);
		// 		screenBuffer[screenBufferIndex] = brightnessChars[brightnessCharIndex];
		// 		screenBufferIndex++;
		// 	}
	
		// 	// add new line characters for every row except for the last one
		// 	if (i < (frame.rows - 1)) {
		// 		screenBuffer[screenBufferIndex] = '\n';
		// 		screenBufferIndex++;
		// 	}
		// }	
		
		// clear screen, then render screenBuffer
		
		
 	}

	printf("\e[?25h");

 	return 0;

}
