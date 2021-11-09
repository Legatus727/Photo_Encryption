CC = g++
CFLAGS = -std=c++11 -g -Wall -Werror -pedantic
OBJECTS = PhotoEncrypt.o FibLFSR.o
EXEC = PhotoEncrypt
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: $(EXEC)

PhotoEncrypt: PhotoEncrypt.o FibLFSR.o
	$(CC) $(CFLAGS) -o $(EXEC) PhotoEncrypt.o FibLFSR.o $(SFML)

PhotoEncrypt.o: PhotoEncrypt.cpp
	$(CC) $(CFLAGS) -c PhotoEncrypt.cpp -o PhotoEncrypt.o $(SFML)

FibLFSR.o: FibLFSR.cpp
	$(CC) $(CFLAGS) -c FibLFSR.cpp -o FibLFSR.o

clean:
	rm $(OBJECTS) $(EXEC)