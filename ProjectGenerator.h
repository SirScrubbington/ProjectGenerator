#ifndef PROJECT_GENERATOR_H
#define PROJECT_GENERATOR_H

#ifdef _WIN32
	#include <windows.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FILENAME_LEN 255
#define MAX_FILES 255
#define HASH_LEN 32

#define CREATE_C 1
#define CREATE_H 2
#define FORCE_REPLACE 4
#define CREATE_MAKE 8
#define CREATE_MAIN 16
#define CREATE_CPP 32

void hashFunc(int len, char * str);
char getRandomASCII(int type);

#endif // PROJECT_GENERATOR_H