#ifndef PROJECT_GENERATOR_H
#define PROJECT_GENERATOR_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FILENAME_LEN 255
#define HASH_LEN 32

void hashFunc(int len, char * str);
char getRandomASCII(int type);

#endif // PROJECT_GENERATOR_H