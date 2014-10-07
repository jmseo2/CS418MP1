OBJS = main.o
EXENAME = mp1

COMPILER = g++
WARNINGS =
COMPILER_OPTS = -Wno-deprecated -c -g -O0 $(WARNINGS)
LINKER = g++
LDFLAGS = -framework OpenGL -framework GLUT

UNAME := $(shell uname)

all: $(EXENAME)

$(EXENAME): main.o
	$(LINKER) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o: main.cpp
	$(COMPILER) $(COMPILER_OPTS) main.cpp

