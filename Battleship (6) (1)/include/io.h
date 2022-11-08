#include "record.h"
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <dirent.h> 




#ifndef io_h
#define io_h



#define IN_SIZE 256

int In;
int Out;

void setOUTIN(int c);

// prints a single character to standard out
void printc(char c);

// prints the given string to standard out
void prints(char* s);

// prints a newline to standard out
void println();

void inputs(char *dst[], int size);

void inputInt(char* dst);

#endif