
#ifndef record_h
#define record_h
#include "io.h"

;
void init();
int validateUsername(char* user);
int readFile(char* user, char*** dest);
int writeFile(char* user, int* bowCords, int* innerBowCords ,int* innerSternCords,int* sternCords);

#endif