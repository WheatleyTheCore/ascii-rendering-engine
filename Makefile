CC = g++
CFLAGS = -I/usr/local/include -I/usr/local/include/gsl `gsl-config --cflags --libs` -g -Wall 
SRCS = main.cpp render.c matrixMath.c
PROG = render

DEPS = render.h
OBJ = main.o render.o matrixMath.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROG):$(OBJ)

	$(CC) -o $@ $^ $(CFLAGS)
