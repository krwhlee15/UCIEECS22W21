#ifndef PLAY_H
#define PLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct {
	int p_num;		/* Player Number */
	char p_char;	/* Player Character */
	char p_color;	/* Player Color */
	char move[3];
	int board[3][3];
} PLAY;

PLAY *CreatePlay(int number, char character, char color, char move[3], int board[3][3]);

void DeletePlay(PLAY *p);

#endif
