all: main

CC=gcc
CFLAGS		= -W -Wall
CLIBS		= -Iinclude -Llib -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image -lm
SOURCES		= main.c
OBJECTS		= $(SOURCES:.c = .o)
EXECUTABLE	= main

all: $(SOURCES) 

main: main.o
	$(CC)  main.o -o main.out $(CLIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -rf *.o *.out