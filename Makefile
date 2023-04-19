CC = g++
CFLAGS = -g -Wall
SRCS = main.cpp
PROG = render


$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS)
