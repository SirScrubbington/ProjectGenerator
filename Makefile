# Filename: Makefile
# Author: Scrubbs
# Date: 2018-6-30
# Description: ProjectGenerator Makefile

#Project Name (executable)
PROJECT = pgen

#Compiler
CXX = g++

#Source Files
SOURCE = $(wildcard *.c)

#Object Files
OBJECTS = $(SOURCE:.cpp=.o)

#Build Executable
$(PROJECT): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

#Clean up additional files
.PHONY: clean
clean:
	rm -f $(OBJECT) $(PROJECT)