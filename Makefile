CC=g++
OBJECTS=main.o
DEPENDENCIES=Makefile
CFLAGS=-I/opt/simgrid/include
EXECUTABLE_NAME=main
LDFLAGS=-lsimgrid

all: main

%.o: %.cpp $(DEPENDENCIES)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXECUTABLE_NAME): $(OBJECTS) $(DEPENDENCIES)
	$(CC) -o $@ $(OBJECTS) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE_NAME)

run: all
	./$(EXECUTABLE_NAME)
