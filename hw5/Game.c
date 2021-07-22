#include "Game.h"
#include "PlayList.h"

// This function prints the board
void print_fun(int board[3][3], PLAY *p1, PLAY *p2)
{
	char p1_char = p1 -> p_char;
	char p2_char = p2 -> p_char;
	char p1_color = p1 -> p_color;
	char p2_color = p2 -> p_color;
 
    // start with row
    for(int i=0;i<3;i++)
	{
        // print out vertical legend
		if(i==0)
			printf("C ");
		if(i==1)
			printf("B ");
		if(i==2)
			printf("A ");
	
        // find corresponding column    
		for(int j=0;j<3;j++)
		{
			if(board[i][j]==0) // empty space
				printf(" ");
			else if (board[i][j]==1) // player 1
			{
				if (p1_color == 'r')
				{
					printf("\x1b[31m%c\x1b[0m",p1_char); //Red
				}
				else if (p1_color == 'g')
				{
					printf("\x1b[32m%c\x1b[0m",p1_char); //Green
				}
				else if (p1_color == 'y')
				{
					printf("\x1b[33m%c\x1b[0m",p1_char); // Yellow
				}
				else if (p1_color == 'b')
				{
					printf("\x1b[34m%c\x1b[0m",p1_char); // Blue
				}
				else
				{
					printf("%c\x1b[0m",p1_char); // Default color (theme dependent)
				}
			}
			else if (board[i][j]==2) // player 2
			{
				if (p2_color== 'r')
				{
					printf("\x1b[31m%c\x1b[0m",p2_char); //Red
				}
				else if (p2_color== 'g')
				{
					printf("\x1b[32m%c\x1b[0m",p2_char); //Green
				}
				else if (p2_color== 'y')
				{
					printf("\x1b[33m%c\x1b[0m",p2_char); // Yellow
				}
				else if (p2_color== 'b')
				{
					printf("\x1b[34m%c\x1b[0m",p2_char); // Blue
				}
				else
				{
					printf("%c\x1b[0m",p2_char); // Default color (theme dependent)
				}
			}
			
			// print out lines in between columns
			if(j!=2)
				printf("|");
		}
		if(i!=2)
			printf("\n -------\n");
		else if(i==2)
			printf("\n  1 2 3\n");
	}
}

void replay_print_fun(int board[3][3], PLAY *p1, PLAY *p2, FILE *fp)
{
	char p1_char = p1 -> p_char;
	char p2_char = p2 -> p_char;
	 
    // start with row
    for(int i=0;i<3;i++)
	{
        // print out vertical legend
		if(i==0)
			fprintf(fp, "C ");
		if(i==1)
			fprintf(fp, "B ");
		if(i==2)
			fprintf(fp, "A ");
	
        // find corresponding column    
		for(int j=0;j<3;j++)
		{
			if(board[i][j]==0) // empty space
				fprintf(fp," ");
			else if (board[i][j]==1) // player 1
			{
					fprintf(fp, "%c",p1_char); // Default color (theme dependent)
			}
			else if (board[i][j]==2) // player 2
			{
					fprintf(fp, "%c",p2_char); // Default color (theme dependent)
			}
			
			// print out lines in between columns
			if(j!=2)
				fprintf(fp, "|");
		}
		if(i!=2)
			fprintf(fp, "\n -------\n");
		else if(i==2)
			fprintf(fp, "\n  1 2 3\n");
	}
}

//This function checks if there is empty place in board.
int is_there_empty_cell(int board[3][3])
{
	int count=0;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(board[i][j]==0)
				count++;
		}
	}
	if (count!=0)
		return 1; // we have empty cell
	else
		return 0; // we do not have empty cell
}

// win condition
int IsWin(int board[3][3])
{
	int win_flag=0;
	if(((board[0][0]==1)&&(board[1][0]==1)&&(board[2][0]==1))||
		((board[0][1]==1)&&(board[1][1]==1)&&(board[2][1]==1))||
		((board[0][2]==1)&&(board[1][2]==1)&&(board[2][2]==1))||
		((board[0][0]==1)&&(board[0][1]==1)&&(board[0][2]==1))||
		((board[1][0]==1)&&(board[1][1]==1)&&(board[1][2]==1))||
		((board[2][0]==1)&&(board[2][1]==1)&&(board[2][2]==1))||
		((board[0][0]==1)&&(board[1][1]==1)&&(board[2][2]==1))||
		((board[0][2]==1)&&(board[1][1]==1)&&(board[2][0]==1)))
		{
			win_flag =1;
		}

	else if(((board[0][0]==2)&&(board[1][0]==2)&&(board[2][0]==2))||
		((board[0][1]==2)&&(board[1][1]==2)&&(board[2][1]==2))||
		((board[0][2]==2)&&(board[1][2]==2)&&(board[2][2]==2))||
		((board[0][0]==2)&&(board[0][1]==2)&&(board[0][2]==2))||
		((board[1][0]==2)&&(board[1][1]==2)&&(board[1][2]==2))||
		((board[2][0]==2)&&(board[2][1]==2)&&(board[2][2]==2))||
		((board[0][0]==2)&&(board[1][1]==2)&&(board[2][2]==2))||
		((board[0][2]==2)&&(board[1][1]==2)&&(board[2][0]==2)))
		{
			win_flag =2;
		}

	return win_flag;
}

// enters int 1 or 2 in desired position.
void entered_one_char(int board [3][3],PLAY *p)
{
    int valid_entered = 0;
    int c;
    int r;
    while(valid_entered == 0)
    {
        char letters_num[2];
        c=0;
        r=0;
        scanf("%s",letters_num);
		p->move[0] = letters_num[0];
		p->move[1] = letters_num[1];
	
        if (letters_num[0]=='A')
        {
            r=2;
        }
        else if(letters_num[0]=='B')
        {
            r=1;
        }
        else if(letters_num[0]=='C')
        {
            r=0;
        }

        if (letters_num[1]=='1')
        {
            c=0;
        }
        else if(letters_num[1]=='2')
        {
            c=1;
        }
        else if(letters_num[1]=='3')
        {
            c=2;
        }

        if (board[r][c] == 0)
        {
            valid_entered = 1;
        }
        else
        {
            printf("The entered position is not available! Please try again...\n");
        }
    }
    board[r][c]= p->p_num;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			p->board[i][j] = board[i][j];
		}
	}
}

// Handle a Human v. Human game
void HumanVsHuman(int board[3][3], PLAY *p1, PLAY *p2, PLIST *l)
{
	printf("Human v. Human game started\n");
	print_fun(board,p1,p2);
	int tie=1;
	while((is_there_empty_cell(board)))
	{
		printf("Player 1, please choose your move:");
		entered_one_char(board,p1);
		
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				p1->board[i][j] = board[i][j];
			}
		}

		AppendPlaySnapshot(l, p1);
		PrintPlayList(l);			

		print_fun(board,p1,p2);
		int win_flag = IsWin(board);
		if(win_flag != 0)
		{
			if (win_flag == 1)
			{
				printf("Player 1 wins! Game Over!\n\n");
			}
			else if (win_flag == 2)
			{
				printf("Player 2 wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
		else if (is_there_empty_cell(board)==0)
			break;
	
		printf("Player 2, please choose your move:");
		entered_one_char(board,p2);

		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				p2->board[i][j] = board[i][j];
			}
		}
		
		AppendPlaySnapshot(l,p2);
		PrintPlayList(l);

		print_fun(board,p1,p2);
		win_flag = IsWin(board);
		if(win_flag != 0)
		{
			if (win_flag == 1)
			{
				printf("Player 1 wins! Game Over!\n\n");
			}
			else if (win_flag == 2)
			{
				printf("Player 2 wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
	}
	if (tie==1)
		printf("The game is a tie!\n");
}

int minimax(int board[3][3], int player)
{
	int winner = IsWin(board);
	int p = (player == 1) ? -1 : 1;   
	if(winner == 1)
	{
		winner = -1;
	}
	if(winner == 2)
	{
		winner = 1;
	}
	if(winner != 0)
	{
		return winner*p;
	}
	
    int moverow = -1;
	int movecol = -1;
    int score = -2;

    for(int j = 0; j < 3; ++j)
	{
		for(int i = 0; i < 3; ++i)
		{
       		if(board[i][j] == 0)
			{
     	  		board[i][j] = player;
       			int thisScore = -minimax(board, (player == 1) ? 2 : 1);
       	   		if(thisScore > score)
				{
					score = thisScore;
					moverow = i;
					movecol = j;
				}
				board[i][j] = 0;
    	    }
		}
    }
    if(moverow == -1 || movecol == -1)
	{
		return 0;
	}
    return score;
}

char row_char(int i)
{
    char r;
    if (i==2)
    {
        r='A';
    }
    else if(i==1)
    {
        r='B';
    }
    else if(i==0)
    {
        r='C';
    }
	return r;
}

char col_char(int j)
{
    char r;
    if (j==0)
    {
        r='1';
    }
    else if(j==1)
    {
        r='2';
    }
    else if(j==2)
    {
        r='3';
    }
	return r;
}

void ResetBoard(int board[3][3])
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			board[i][j] = 0;
		}
	}
}

void TakeBack(int board[3][3], PLIST *l)
{
	RemoveLastPlay(l);
	PrintPlayList(l);
	RemoveLastPlay(l);
	PrintPlayList(l);

	PENTRY *e;
	PLAY *p;
	
	e = l->Last;
	p = &(e->Play);
	
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			board[i][j] = p->board[i][j];
		}
	}
}
