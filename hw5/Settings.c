#include "Settings.h"

// players can choose their characters.
void choose_char(PLAY *p1, PLAY *p2)
{
	char player1_char = p1 -> p_char;
	char player2_char = p2 -> p_char;

	printf("player 1 choose your char between A to Z\n");
	scanf("%c", &player1_char);
	getchar();
	printf("player 2 choose your char between A to Z\n");
	scanf("%c", &player2_char);
	getchar();
	p1 -> p_char = player1_char;
	p2 -> p_char = player2_char;
}

// players can choose their colors.
void choose_color(PLAY *p1, PLAY *p2)
{
	int valid_entered = 0;
	printf("player 1 choose from the following list for your color please...\n");
	printf("'r' for red, 'g' for green, 'y' for yellow, 'b' for blue', 'd' for default\n");
	while (valid_entered == 0)
	{
		char col;
		scanf("%c",&col);
		getchar();
		if (col=='r' || col=='g' || col=='y' || col=='b' || col=='d')
		{
			p1 -> p_color = col;
			valid_entered = 1;
		}
		else
		{
			printf("Invalid input, please try agian ...\n");
		}
	}
	valid_entered = 0;
	printf("player 2 choose from the following list for your color please...\n");
	printf("'r' for red, 'g' for green, 'y' for yellow, 'b' for blue', 'd' for default\n");
	while (valid_entered == 0)
	{
		char col;
		scanf("%c",&col);
		getchar();
		if (col=='r' || col=='g' || col=='y' || col=='b' || col=='d')
		{
			p2 -> p_color = col;
			valid_entered = 1;
		}
		else
		{
			printf("Invalid input, please try agian ...\n");
		}
	}
}

// handle settings for the game
void settings(PLAY *p1, PLAY *p2)
{
	int valid_entered = 0;
	while (valid_entered == 0)
	{
		int select = 0;
		printf("Entering Settings...\n");
		printf("Please enter the setting options below...\n");
		printf("1. Changing the players' character\n");
		printf("2. Changing players' character color\n");
		printf("3. Exiting setting\n");
		scanf("%d",&select);
		getchar();

		if (select == 1)
		{
			choose_char(p1, p2);
		}
		else if (select == 2)
		{
			choose_color(p1, p2);
		}
		else if (select == 3)
		{
			break;
		}
		else
		{
			printf("Invalid input. Please try again...\n");
		}
	}
	printf("Setting completed!\n");
}
