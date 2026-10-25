# Author: Logan Smouter
# Date: 10/16/2026
# Description: Build the vector calculator and remove generated build files.
# Compilation: $ make

CC = gcc
CFLAGS = -Wall
TARGET = minimat
OBJECTS = main.o myveclab.o myvectarray.o myvectop.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

main.o: main.c myveclab.h
	$(CC) $(CFLAGS) -c main.c

myveclab.o: myveclab.c myveclab.h myvect.h myvectarray.h myvectop.h
	$(CC) $(CFLAGS) -c myveclab.c

myvectarray.o: myvectarray.c myvectarray.h myvect.h
	$(CC) $(CFLAGS) -c myvectarray.c

myvectop.o: myvectop.c myvectop.h myvect.h
	$(CC) $(CFLAGS) -c myvectop.c

clean:
	rm -f $(TARGET) $(OBJECTS)
