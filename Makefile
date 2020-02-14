#The compiler to be used
CC=g++
#Linker flags
LFLAGS=-lSDL2 -lSDL2main -lSDL2_image -lGLEW -lGL

exec: compile
	./a.out
compile: *.cpp
	g++ -c *.cpp
	g++ *.o $(LFLAGS)