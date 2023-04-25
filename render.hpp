#ifndef RENDER_H
#define RENDER_H 1

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

long mapValue(long x, long in_min, long in_max, long out_min, long out_max);

void pixel(char* screenBuffer, int x, int y, int brightness);

void line(char* screenBuffer, int x1, int y1, int x2, int y2, int brightness);

void flushBuffer(char* screenBuffer);

void drawScreen(char* screenBuffer, char* nextScreenBuffer);

struct vec3 {
    int x;
    int y;
    int z;
};

#endif