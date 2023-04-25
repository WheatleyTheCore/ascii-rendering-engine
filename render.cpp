#include "render.hpp"
#include <math.h>
#include <stdio.h>
#include <unistd.h>


extern int SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BUFFER_LEN;

static char brightnessChars[] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.                         ";


// map function for mapping number from one range to another (for going from brigtness values to brightness chars)
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
	}
	clear();
	gotoxy(0, 0);
}

void drawScreen(char* screenBuffer, char* nextScreenBuffer) {
	// for (int i = 0; i < SCREEN_BUFFER_LEN; i++) {
	// 	printf("%c", screenBuffer[i]);
	// }

	clear();
	gotoxy(0, 0);

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			if (screenBuffer[y * SCREEN_WIDTH + x + y] == nextScreenBuffer[y * SCREEN_WIDTH + x + y]) {
				continue;
			}
			gotoxy(x, y);
			printf("%c", nextScreenBuffer[y * SCREEN_WIDTH + x + y]);
		}

		// add new line characters for every row except for the last one
		if (y < (SCREEN_HEIGHT - 1)) {
			printf("%c", '\n');
		}
	}
	sleep(1);

	
}