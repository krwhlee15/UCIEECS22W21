#include "Play.h"

PLAY *CreatePlay(int number, char character, char color, char move[3], int board[3][3])
{
	PLAY *p;
	p = malloc(sizeof(PLAY));
	p->p_num = number;
	p->p_char = character;
	p->p_color = color;
	p->move[0] = -1;
	p->move[1] = -1;
	p->move[2] = 0;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			p->board[i][j] = board[i][j];
		}
	}
	return p;
}

void DeletePlay(PLAY *p)
{
	free(p);
}

