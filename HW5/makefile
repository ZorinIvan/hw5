#This is a Makefile for files
CCC=g++
CXXFLAGS=-Wall -g
CXXLINK=$(CCC)
OBJS=Main.o Directory.o FilesIterator.o TextFile.o File.o
RM=rm -f

#Default target (usually "all")
all: files

#Creating the executables
files:$(OBJS)
	$(CXXLINK) -o files $(OBJS)  


#Creating object files using default rules
File.o:File.h File.cpp
TextFile.o:File.h TextFile.h TextFile.cpp
FilesIterator.o:File.h Directory.h FilesIterator.h FilesIterator.cpp
Directory.o:File.h Directory.h Directory.cpp
Main.o:File.h Directory.h TextFile.h FilesIterator.h Main.cpp

#Cleaning old files before new make
clean:  
	$(RM) files *.o *.bak *~ "#"* core
