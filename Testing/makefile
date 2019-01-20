# set the default compilation command and default flags
CC = g++
#CC = mpicxx
CFLAGS =  -lm -O4 -std=c++11
DFLAGS =  -lm -O0 -ggdb -std=c++11

# used to direct executables to a bin directory

# this is a list of the object files used to compile executible
OBJ = 

# default target
all: file_io

# do all the linking and make the executible

file_io:
	$(CC) $(CFLAGS) FileIO_test.cpp $(OBJ) -o File_io.out
	./File_io.out
clean:
	rm *.out