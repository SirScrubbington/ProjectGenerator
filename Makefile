# Filename: Makefile
# Author: Scrubbs
# Date: 2018-6-16
# Description: 

all: pgen

pgen:
	gcc -o pgen ProjectGenerator.c
	
clean:
	rm *.o
