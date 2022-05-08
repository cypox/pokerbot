CC = g++
CFLAGS = -std=c++17
LIBS = -lpthread


all: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp -o main $(LIBS)
