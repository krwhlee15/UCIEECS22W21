/****************************************/
/* TicTacWhoa.c                         */
/* authors: Wonhee Lee                  */
/*                                      */
/* modifications:                       */
/* <insert your mod here>               */
/* 2021/01/08	WL	Initial Version     */
/****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED	    "\x1b[31m"
#define BLUE	"\x1b[34m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define RESET	"\x1b[0m"

/* Initial size of the game */
/* Can be modified through game settings */
int len = 3;
char p1char = 'X';
char p2char = 'O';
char p1color = 'D';
char p2color = 'D';

void Menu(void);
void PrintGame(char arr[][10]);
void Settings(void);
void Reset(char arr[][10]);
char Win(char arr[][10], int a, int b);
int Draw(char arr[][10]);

int main(void)
{
	srand(time(NULL));

	int option;
	char winner = '\0';
	char row, col;	
	char player;
	int newrow, newcol;
	char game[10][10];	
	int airow,aicol;
	int pchar, aichar;
	int p;
	
	Reset(game);	

	while (1)
	{
		Menu();
		scanf("%d", &option);
	
		/* 1. Human v. Human */	
		if(option == 1)
		{
			printf("Human v. Human game started\n");
			player = p1char;
			while(!winner && !Draw(game))
			{
				PrintGame(game);

				printf("Player %c, please choose your move: ", player);
				scanf(" %c %c", &row, &col);
				printf("Player %c chose %c%c\n", player, row, col);
			
				newrow = len-1-(row-'A');
				newcol = col-'1';
				game[newrow][newcol] = player;
			
				if (player == p1char)
				{
					player = p2char;
				}
				else
				{
					player = p1char;
				}
				winner = Win(game, newrow, newcol);
			}
			PrintGame(game);
			if (winner == p1char || winner == p2char)
			{
				printf("Player %c wins! Game Over!\n", winner);
				winner = '\0';
				Reset(game);
			}
			else if (Draw(game))
			{
				printf("Draw! Game Over!\n");
				Reset(game);
			}
		}
		/* 2. Human v. AI */
		else if (option == 2)
		{
			printf("Player 1 or Player 2? (Type 1 or 2): ");
			scanf("%d", &p);
			switch (p)
			{
				case 1:
					pchar = p1char;
					aichar = p2char;
					break;
				case 2:
					pchar = p2char;
					aichar = p1char;
					break;
				default:
					pchar = p1char;
					aichar = p2char;
					break;
			}
			printf("Human v. AI game started\n");
			
			if (aichar == p1char)
			{
				PrintGame(game);
					
				do
				{
				airow = rand()%len;
				aicol = rand()%len;		
				} while (game[airow][aicol] != ' ');
			
				game[airow][aicol] = aichar;
				printf("AI chose %c%c\n", 'A'+len-1-airow, aicol+'1');
				winner = Win(game, airow, aicol);
			}
			
			while(!winner && !Draw(game))
			{
				PrintGame(game);
				printf("Player, please choose your move: ");
				scanf(" %c %c", &row, &col);
				printf("Player chose %c%c\n", row, col);
				
				newrow = len-1-(row-'A');
				newcol = col-'1';

				game[newrow][newcol] = pchar;	
				winner = Win(game, newrow, newcol);	
				if(!(!winner && !Draw(game)))
				{
					break;
				}	

				PrintGame(game);
					
				do
				{
				airow = rand()%len;
				aicol = rand()%len;		
				} while (game[airow][aicol] != ' ');
				
				game[airow][aicol] = aichar;
				printf("AI chose %c%c\n", 'A'+len-1-airow, aicol+'1');
				winner = Win(game, airow, aicol);
			}
			PrintGame(game);
			if (winner == pchar)
			{
				printf("Player wins! Game Over!\n");
				winner = '\0';
				Reset(game);
			}
			else if(winner == aichar)
			{
				printf("AI wins! Game Over!\n");
				winner = '\0';
				Reset(game);
			}
			else
			{
				printf("Draw! Game Over!\n");
				Reset(game);
			}
		}
		/* 3. Game Settings */
		else if(option == 3)
		{
			Settings();
			Reset(game);
		}
		/* 4. Exit the game */
		else if (option == 4)
		{
			break;
		}
	} 
}

/* Resets the game */
void Reset(char arr[][10])
{
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<len;j++)
		{
			arr[i][j] = ' ';
		}
	}

}

/* Prints Menu */
void Menu(void)
{
	printf("Welcome to Secure-Tic-Tac-Whoa!\n");
	printf("1. Start New Game (Human v. Human)\n");
	printf("2. Start New Game (Human v. AI)\n");
	printf("3. Game Settings\n");
	printf("4. Exit Game\n");
	printf("Choose Option: ");
}

/* Prints the game */
void PrintGame(char arr[][10])
{
	int row, col;
	int i;

	for (row=0;row<len;row++)
	{
		printf("%c ", ('A'+len-1-row));
		for(col=0;col<len;col++)
		{
			if(arr[row][col] == p1char)
			{
				switch(p1color)
				{
					case 'R':
						printf(RED "%c" RESET, arr[row][col]);
						break;
					case 'B':
						printf(BLUE "%c" RESET, arr[row][col]);
						break;
					case 'G':
						printf(GREEN "%c" RESET, arr[row][col]);
						break;
					case 'Y':
						printf(YELLOW "%c" RESET, arr[row][col]);
						break;
					default:
						printf("%c", arr[row][col]);
						break;
				}
			}
			else if(arr[row][col] == p2char)
			{
				switch(p2color)
				{
					case 'R':
						printf(RED "%c" RESET, arr[row][col]);
						break;
					case 'B':
						printf(BLUE "%c" RESET, arr[row][col]);
						break;
					case 'G':
						printf(GREEN "%c" RESET, arr[row][col]);
						break;
					case 'Y':
						printf(YELLOW "%c" RESET, arr[row][col]);
						break;
					default:
						printf("%c", arr[row][col]);
						break;
				}	
			}
			else
			{
				printf("%c", arr[row][col]);
			}
			if(col != len-1)
			{
			printf("|");
			}
		}
		printf("\n ");
		if(row == len-1)
		{
			break;
		}
		printf(" ");
		for(i=0;i<(2*len)-1;i++)
		{
			printf("-");
		}
		printf("\n");		
	}
	for(i=1;i<=len;i++)
	{
		printf(" %d", i);
	}
	printf("\n");
}

/* Sets the size of the game */
void Settings(void)
{
	int c;
	int x;
	printf("1. Game size\n");
	printf("2. Player 1 Color/Character\n");
	printf("3. Player 2 Color/Character\n");
	printf("Choose Option: ");
	scanf("%d", &c);	

	switch(c)
	{
		case 1:
			printf("Current size of the game: %dx%d\n", len, len);
			printf("Input new size of the game(up to 10): ");
			scanf("%d", &x);
			len = x;
			printf("New size of the game: %dx%d\n", x, x);	
			break;
		case 2:
			printf("Available colors: Red(R), Blue(B), Green(G), Yellow(Y), Default(D)\n");
			printf("Current player 1 Color/Character: %c, %c\n", p1color, p1char);
			printf("Input new color for player 1(R, B, G, Y, D): ");
			scanf(" %c", &p1color);
			printf("Input new Character for player 1: ");
			scanf(" %c", &p1char);
			printf("Color/Character for player 1: %c / %c\n", p1color, p1char);
			break;
		case 3:	
			printf("Available colors: Red(R), Blue(B), Green(G), Yellow(Y), Default(D)\n");
			printf("Current player 2 Color/Character: %c, %c\n", p2color, p2char);
			printf("Input new color for player 2(R, B, G, Y, D): ");
			scanf(" %c", &p2color);
			printf("Input new Character for player 2: ");
			scanf(" %c", &p2char);
			printf("Color/Character for player 2: %c / %c\n", p2color, p2char);
			break;
	}
}

/* Check if the input is a winning move */
char Win(char arr[][10], int a, int b)
{	
	int i;
	int count=1;
	
	/* check for column */
	for(i=1;i<len;i++)
	{
		if (arr[a][b] == arr[a][(b+i)%len])
		{
			count *= 1;	
		}
		else
		{
			count *= 0;
		}
	}
	if (count == 1)
	{
		return arr[a][b];
	}

	/* count reset */
	count = 1;
	
	/* check for row */
	for(i=1;i<len;i++)
	{
		if (arr[a][b] == arr[(a+i)%len][b])
		{
			count *= 1;	
		}
		else
		{
			count *= 0;
		}
	}
	if (count == 1)
	{
		return arr[a][b];
	}

	/* count reset */
	count = 1;
	
	/* check for forward diagonal */
	for(i=1;i<len;i++)
	{
		if (a == b && arr[a][b] == arr[(a+i)%len][(b+i)%len])
		{
			count *= 1;	
		}
		else
		{
			count *= 0;
		}
	}
	if (count == 1)
	{
		return arr[a][b];
	}

	/* count reset */
	count = 1;
	
	/* check for reverse diagonal */
	for(i=1;i<len;i++)
	{
		if (a+b == len-1 && arr[a][b] == arr[(a+(len-i))%len][(b+i)%len])
		{
			count *= 1;	
		}
		else
		{
			count *= 0;
		}
	}
	if (count == 1)
	{
		return arr[a][b];
	}

	return 0;
}

/* Check if there is any empty space, and returns 1 if there is no empty space */
int Draw(char arr[][10])
{
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<len;j++)
		{
			if(arr[i][j] == ' ')
			{
				return 0;
			}
		}
	}
	return 1;
}
