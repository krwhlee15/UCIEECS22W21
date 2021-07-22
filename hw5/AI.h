#ifndef AI_H
#define AI_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "Game.h"
#include "Play.h"

void Inky(int board[3][3], PLAY *p1, PLAY *p2, PLIST *l);

void Blinky(int board[3][3], PLAY *p1, PLAY *p2, PLIST *l);

void Pinky(int board[3][3], PLAY *p1, PLAY *p2, PLIST *l);

void Clyde(int board[3][3], PLAY *p1, PLAY *p2, PLIST *l);

#endif
