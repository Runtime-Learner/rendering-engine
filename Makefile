# A simple Makefile for compiling small SDL projects

# set the compiler
CC := g++

# set the compiler flags
CFLAGS :=  --std=c++14 -Wall 

# set the folder hierarchy
SRC := ./src
BIN := ./bin
LIB := ./lib

# add header files here
HDRS := $(LIB)/eigen3/Eigen/ /usr/include/c++/9 /usr/include/x86_64-linux-gnu/c++/9

# add source files here
SRCS := $(SRC)/main.cpp #file-name.c

# generate names of object files
OBJS := $(SRCS:.cpp=.o)

# name of executable
EXEC := $(BIN)/app #name your executable file

# default recipe
all: $(EXEC)
 
showfont: showfont.cpp Makefile
	$(CC) -o $@ $@.cpp $(CFLAGS) $(LIBS)

glfont: glfont.cpp Makefile
	$(CC) -o $@ $@.cpp $(CFLAGS) $(LIBS)

# recipe for building object files
$(OBJS): $(@:.o=.cpp) $(HDRS) Makefile
	$(CC) -o $@ $(@:.o=.cpp) -c $(CFLAGS)


# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)
	rm -f $(OBJS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
