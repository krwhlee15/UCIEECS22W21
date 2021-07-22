#ifndef GAME_H
#define GAME_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Play.h"
#include "PlayList.h"

void print_fun(int board[3][3], PLAY *p1, PLAY *p2);

void replay_print_fun(int board[3][3], PLAY *p1, PLAY *p2, FILE *fp);

int is_there_empty_cell(int board[3][3]);

int IsWin(int board[3][3]);

void entered_one_char(int board[3][3], PLAY *p);

void HumanVsHuman(int board[3][3], PLAY *p1, PLAY *p2, PLIST *l);

int minimax(int board[3][3], int player);

char row_char(int i);

char col_char(int j);

void TakeBack(int board[3][3], PLIST *l);

void ResetBoard(int board[3][3]);

#endif
