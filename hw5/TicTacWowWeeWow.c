/*********************************************************************/
/* Reference solution for Assignment 1 for EECS 22 @ UCI Winter 2021 */
/*                                                                   */
/* This is an "A" level representation of the Tic-Tac-Whoa game.     */
/* There are improvements that can be made, but this is considered   */
/* very good.                                                        */
/*                                                                   */
/* This solution is for your reference for this course and           */
/* copyright belongs to the authors below. Reproduction or sharing   */
/* of this code outside of this class is prohibited except with the  */
/* express written consent of the authors.                           */
/*                                                                   */
/* Authors: Mozhgan Moradiganjeh, QV Dang, Wonhee Lee                */
/* Modifications:                                                    */
/* 03/11/21 WL  final updates for Assignment 5						 */
/* 01/18/21 QV  AI, function, and comment updates                    */
/* 01/13/21 MM  Initial version                                      */
/*********************************************************************/
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "Game.h"
#include "AI.h"
#include "Settings.h"
#include "Play.h"

// Handle Menu Options
int print_menu()
{
	int select=0;
	printf("1. Start New Game (Human v. Human)\n");
	printf("2. Start New Game (Human v. AI)\n");
	printf("3. Game Settings\n");
	printf("4. Exit Game\n");
	printf("Choose Option: ");
	scanf("%d",&select);
	getchar(); // one solution for clearing the "\n" char from the input
	return select;
}

PLIST *l = NULL;
int debug = 0;

void Replay(int AI_option, PLAY *p1, PLAY *p2, PLIST *l)
{	
	struct tm *t;
	time_t timer;

	timer = time(NULL);	
	t = localtime(&timer);

	PENTRY *e;
	PLAY *p;

	e = l->First;

	char name[256];
	sprintf(name, "TTWvAI-%d-%02d-%02d.txt", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
		
	FILE *fp = fopen(name, "w");
	fputs("#TicTacWowWeeWow\n", fp);
	fputs("Version: v2\n", fp);
	fprintf(fp, "Filename: %s\n", name);
	fprintf(fp, "Date: %d/%02d/%02d %d:%02d\n\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);

	fputs("#Settings\n", fp);
	char *AI;
	char *p1_color;
	char *p2_color;
	switch(AI_option)
	{
		case 1:
			AI = "Inky";
			break;
		case 2:
			AI = "Blinky";
			break;
		case 3:
			AI = "Pinky";
			break;
		case 4:
			AI = "Clyde";
			break;
	}
	switch(p1->p_color)
	{
		case 'r':
			p1_color = "Red";
			break;
		case 'g':
			p1_color = "Green";
			break;
		case 'y':
			p1_color = "Yellow";
			break;
		case 'b':
			p1_color = "Blue";
			break;
		case 'd':
			p1_color = "Default";
			break;
	}

	switch(p2->p_color)
	{
		case 'r':
			p2_color = "Red";
			break;
		case 'g':
			p2_color = "Green";
			break;
		case 'y':
			p2_color = "Yellow";
			break;
		case 'b':
			p2_color = "Blue";
			break;
		case 'd':
			p2_color = "Default";
			break;
	}
	
	fprintf(fp, "Player 1 (Human): \'%c\', \'%s\'\n", p1->p_char, p1_color);
	fprintf(fp, "Player 2 (AI - %s): \'%c\', \'%s\'\n\n", AI, p2->p_char, p2_color);

	fputs("#Winner\n", fp);
	e = l->Last;
	p = &(e->Play);
	int win_flag = IsWin(p->board);
	
	if(win_flag == 0)
	{
		fprintf(fp, "Tie\n");
	}
	else
	{
		fprintf(fp, "Player %d\n", win_flag);
	}

	fputs("\n#MovesList\n", fp);
	
	e = l->First;
	while(e)
	{
		p = &(e->Play);
		fprintf(fp, "Player %d: %s \n", p->p_num, p->move);
		e = e->Next;
	}

	fputs("\n#Replay\n", fp);
	
	e = l->First;
	while(e)
	{
		p = &(e->Play);
		fprintf(fp, "Player %d chooses %s \n", p->p_num, p->move);
		replay_print_fun(p->board, p1, p2, fp);
		fprintf(fp, "\n");
		e = e->Next;
	}
	
	fputs("#EOF\n", fp);
	fclose(fp);
	printf("Replay Saved.\n");
}


// Main Program for Tic-Tac-Whoa
int main(int argc, char *argv[])
{
    // initialize game
	l = NewPlayList();
	int board[3][3]={{0,0,0},{0,0,0},{0,0,0}};
	char init[2] = "99";
   	PLAY *p1 = CreatePlay(1, 'X', 'd', init, board);
	PLAY *p2 = CreatePlay(2, 'O', 'd', init, board);

    if(argc > 1 && strcmp(argv[1], "-d") == 0)
       debug = 1;
	printf("Welcome to Tic-Tac-Wow-Wee-Wow!\n");
	int done=0;
	while(done==0)
	{
		int option = print_menu();
		int AI_option;
		char ReplayOption;

		switch(option)
		{
			case 1:
				HumanVsHuman(board,p1,p2,l);
				break;
			case 2:
				printf("Level 1 (Inky) - picks first available move\n");
				printf("Level 2 (Blinky) - picks a random available move\n");
				printf("Level 3 (Pinky) - blocks Human from getting 3-in-a-row when possible\n");
				printf("Level 4 (Clyde) - full tree search\n");
				printf("Select a level: ");
				scanf("%d", &AI_option);
				switch(AI_option)
				{
					case 1:
						Inky(board,p1,p2,l);
						break;
					case 2:
						Blinky(board,p1,p2,l);
						break;
					case 3:
						Pinky(board,p1,p2,l);
						break;
					case 4:
						Clyde(board,p1,p2,l);
						break;
				}
				printf("Save Replay? y/n: ");
				scanf(" %c", &ReplayOption);
				switch(ReplayOption)
				{
				case 'y':
					Replay(AI_option, p1, p2, l);
					break;
				default:
					break;
				}
				break;
			case 3:
				settings(p1,p2);
				break;
			case 4:
				printf("Thanks for playing. Exiting game...\n");
				done=1;
				break;
		}
		ResetBoard(board);	
	}
	PrintPlayList(l);
	DeletePlayList(l);
	DeletePlay(p1);
	DeletePlay(p2);
	return 0;
}

/* EOF */
