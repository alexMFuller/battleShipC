#include "record.h"
#ifndef game_h
#define game_h

char gameMap[10][10];

char bx[2];
char by[2];
char sx[2];
char sy[2];

char userX[1];
char userY[1];

int bowCords[2];
int sternCords[2];
int innerBowCords[2];
int innerSternCords[2];


int hideShip(char* user);
int findShip(char* user);
int isValidShip(int bbx,int bby,int ssx,int ssy);

#endif