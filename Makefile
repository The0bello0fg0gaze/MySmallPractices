CC = g++
CFLAGS = -Wall -g -O2
SOURCES = HDML
TARGET = $(SOURCES).exe

all: $(SOURCES).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES).cpp
	./$(TARGET)