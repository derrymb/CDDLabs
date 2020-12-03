#Derry Brennan 27/11/2020
#Makefile for lab6
#Used to contain commands to compile projects
#Equivalent(?) to a project file in VStudio -- only better!
#See http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/ for info.


CC = g++
CFLAGS = -std=c++11 -pthread
OBJFILES = main.o Semaphore.o SafeBuffer.o Event.o
#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: $(OBJFILES)
	$(CC) -o proCon $(OBJFILES) $(CFLAGS) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -DDEBUG -Wall
DEBUG: ALL

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
