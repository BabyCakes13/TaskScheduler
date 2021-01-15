CC=g++
OBJECTS=main.o Task.o Hosts.o Scheduler.o
DEPENDENCIES=Makefile
CFLAGS=-g -I/usr/local/include
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
