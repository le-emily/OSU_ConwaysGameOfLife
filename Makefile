#Makefile for Conway's Game of Life

OBJS = main.o World.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

main : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS)

main.o : main.cpp
	$(CC) $(CFLAGS) main.cpp

World.o : World.h World.cpp
	$(CC) $(CFLAGS) World.cpp

clean:
	rm $(OBJS) a.out
