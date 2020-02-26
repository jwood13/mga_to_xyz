# set the default compilation command and default flags
CC = g++
#CC = mpicxx
GIT_VERSION := $(shell git describe --abbrev=7 --dirty --always --tags)
CFLAGS =  -lm -O4 -std=c++11 -DGIT_DESCRIPTION=\"$(GIT_VERSION)\"
DFLAGS =  -lm -O0 -ggdb -std=c++11 -DGIT_DESCRIPTION=\"$(GIT_VERSION)\" -g

# used to direct executables to a bin directory
BINPATH = .

# this is a list of the object files used to compile executible
OBJ = 

# default target
all: xyz_conversion mga_conversion sphere

# do all the linking and make the executible

xyz_conversion: xyz_conversion.cpp
	$(CC) $(CFLAGS) xyz_conversion.cpp $(OBJ) -o $(BINPATH)/xyz_conversion.out
xyz_conversiondebug: xyz_conversion_debug
	$(CC) $(DFLAGS) xyz_conversion.cpp $(OBJ) -o $(BINPATH)/xyz_conversion_debug.out
mga_conversion: mga_conversion.cpp
	$(CC) $(CFLAGS) mga_conversion.cpp $(OBJ) -o $(BINPATH)/mga_conversion.out
mga_conversiondebug: mga_conversion_debug
	$(CC) $(DFLAGS) mga_conversion.cpp $(OBJ) -o $(BINPATH)/mga_conversion_debug.out
sphere: sphere_conversion.cpp
	$(CC) $(CFLAGS) sphere_conversion.cpp $(OBJ) -o $(BINPATH)/sphere_conversion.out
# running "make clean" should delete all the object files (but NOT SOURCE FILES)
# this is used when you want to rebuild everything
clean:
	rm -f *.o
