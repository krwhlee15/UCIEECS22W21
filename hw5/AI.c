#include "AI.h"
#include "Game.h"
#include "PlayList.h"

// Handle a Human v. AI game
void Inky(int board[3][3], PLAY *p1, PLAY *p2, PLIST *l) // Human is always player1 and AI is player2
{
	printf("Human v. AI game started\n");
	PLAY *d = CreatePlay(0, '0', 'd', "ZZ", board);
	AppendPlaySnapshot(l, d);
	print_fun(board,p1,p2);
	int tie=1;
	int count = 0;
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
				printf("AI wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
		else if (is_there_empty_cell(board)==0)
			break;

		printf("AI is choosing its move:\n");
        int foundMove = 0;
		int i,j;
		for (i=0; i<3; i++)
		{
			for (j=0; j<3; j++)
			{
				if (board[i][j] == 0)
				{
                    board[i][j] = 2;
                    foundMove = 1;
					break;
				}
			}

            if(foundMove)
            {
                break;
            }
		}
		p2 -> move[0] = row_char(i);
		p2 -> move[1] = col_char(j);

		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				p2->board[i][j] = board[i][j];
			}
		}
		
		AppendPlaySnapshot(l, p2);
		PrintPlayList(l);
		print_fun(board,p1,p2);
		win_flag = IsWin(board);
		if(win_flag == 0)
		{
			printf("Take back move? y/n: ");
			char takeback;
			scanf(" %c", &takeback);
			switch(takeback)
			{
				case 'y':
					TakeBack(board,l);
					print_fun(board,p1,p2);
					continue;
				default:
					if(count == 0)
					{
						RemoveFirstPlay(l);
					}
					count++;
					break;
			}
		}
		
		if(win_flag == 2)
		{
			printf("AI won. Take back move? y/n: ");
			char takeback;
			scanf(" %c", &takeback);
			switch(takeback)
			{
				case 'y':
					TakeBack(board,l);
					if (count == 0)
					{
						ResetBoard(board);
					}
					print_fun(board,p1,p2);
					continue;
				default:
					break;
			}
		}
		if(win_flag != 0)
		{
			if (win_flag == 1)
			{
				printf("Player 1 wins! Game Over!\n\n");
			}
			else if (win_flag == 2)
			{
				printf("AI wins! Game Over!\n\n");

			}
			tie=0;
		}
		else if (is_there_empty_cell(board)==0)
			break;
	}
	if (tie==1)
	{
		printf("The game is a tie!\n");
	}
	DeletePlay(d);
}

void Blinky(int board[3][3],PLAY *p1,PLAY *p2, PLIST *l) 
{
	srand(time(NULL));

	printf("Human v. AI game started\n");
	PLAY *d = CreatePlay(0, '0', 'd', "ZZ", board);
	AppendPlaySnapshot(l, d);
	print_fun(board,p1,p2);
	int tie=1;
	int count = 0;
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
				printf("AI wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
		else if (is_there_empty_cell(board)==0)
			break;

		printf("AI is choosing its move:\n");
	
		int foundMove = 0;
		int i,j;
		while(1)
		{
			i = rand()%3;
			j = rand()%3;	
			
			if (board[i][j] == 0)
			{
                board[i][j] = 2;
                foundMove = 1;
				break;
			}

			if(foundMove)
			{
				break;
			}
		}

		p2 -> move[0] = row_char(i);
		p2 -> move[1] = col_char(j);
	
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				p2->board[i][j] = board[i][j];
			}
		}
		
		AppendPlaySnapshot(l, p2);
		PrintPlayList(l);
		print_fun(board,p1,p2);
		win_flag = IsWin(board);
		if(win_flag == 0)
		{
			printf("Take back move? y/n: ");
			char takeback;
			scanf(" %c", &takeback);
			switch(takeback)
			{
				case 'y':
					TakeBack(board,l);
					print_fun(board,p1,p2);
					continue;
				default:
					if(count == 0)
					{
						RemoveFirstPlay(l);
					}
					count++;
					break;
			}
		}
		
		if(win_flag == 2)
		{
			printf("AI won. Take back move? y/n: ");
			char takeback;
			scanf(" %c", &takeback);
			switch(takeback)
			{
				case 'y':
					TakeBack(board,l);
					print_fun(board,p1,p2);
					continue;
				default:
					break;
			}
		}

		if(win_flag != 0)
		{
			if (win_flag == 1)
			{
				printf("Player 1 wins! Game Over!\n\n");
			}
			else if (win_flag == 2)
			{
				printf("AI wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
		else if (is_there_empty_cell(board)==0)
			break;
	}
	if (tie==1)
	{
		printf("The game is a tie!\n");
	}
	DeletePlay(d);
}

void Pinky(int board[3][3],PLAY *p1, PLAY *p2, PLIST *l)
{
	printf("Human v. AI game started\n");
	PLAY *d = CreatePlay(0, '0', 'd', "ZZ", board);
	AppendPlaySnapshot(l, d);
	print_fun(board,p1,p2);
	int tie=1;
	int count = 0;
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
				printf("AI wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
		else if (is_there_empty_cell(board)==0)
			break;

		printf("AI is choosing its move:\n");
    	int foundMove = 0;
		int i, j;
		for (i=0; i<3; i++)
		{
			for (j=0; j<3; j++)
			{
				if (board[i][j] == 0)
				{
                    board[i][j] = 1;
					if(IsWin(board))
					{
						board[i][j] = 2;
						foundMove = 1;
					}
					else
					{
						board[i][j] = 0;
					}
				}
			}
            if(foundMove)
            {
                break;
            }
		}
		while(foundMove == 0)
		{
			i = rand()%3;
			j = rand()%3;	
			
			if (board[i][j] == 0)
			{
  	             board[i][j] = 2;
  	             foundMove = 1;
				break;
			}

			if(foundMove)
			{
				break;
			}
		}
		
		p2 -> move[0] = row_char(i);
		p2 -> move[1] = col_char(j);
		
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				p2->board[i][j] = board[i][j];
			}
		}
		
		AppendPlaySnapshot(l, p2);
		PrintPlayList(l);
		
		print_fun(board,p1,p2);
		win_flag = IsWin(board);
		
		if(win_flag == 0)
		{
			printf("Take back move? y/n: ");
			char takeback;
			scanf(" %c", &takeback);
			switch(takeback)
			{
				case 'y':
					TakeBack(board,l);
					print_fun(board,p1,p2);
					continue;
				default:
					if(count == 0)
					{
						RemoveFirstPlay(l);
					}
					count++;
					break;
			}
		}

		if(win_flag == 2)
		{
			printf("AI won. Take back move? y/n: ");
			char takeback;
			scanf(" %c", &takeback);
			switch(takeback)
			{
				case 'y':
					TakeBack(board,l);
					print_fun(board,p1,p2);
					continue;
				default:
					break;
			}
		}
		
		if(win_flag != 0)
		{
			if (win_flag == 1)
			{
				printf("Player 1 wins! Game Over!\n\n");
			}
			else if (win_flag == 2)
			{
				printf("AI wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
		else if (is_there_empty_cell(board)==0)
			break;
	}
	if (tie==1)
	{
		printf("The game is a tie!\n");
	}
	DeletePlay(d);
}

void Clyde(int board[3][3], PLAY *p1, PLAY *p2, PLIST *l)
{
	printf("Human v. AI game started\n");
	PLAY *d = CreatePlay(0, '0', 'd', "ZZ", board);
	AppendPlaySnapshot(l, d);
	print_fun(board,p1,p2);
	int tie=1;
	int count = 0;
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
				printf("AI wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
		else if (is_there_empty_cell(board)==0)
			break;

		printf("AI is choosing its move:\n");

		int moverow = -1;
		int movecol = -1;
		int score = -2;
		int i,j;
		for (j=0; j<3; j++)
		{
			for (i=0; i<3; i++)
			{
				if (board[i][j] == 0)
				{
                    board[i][j] = 2;
					int tempScore = -minimax(board, 1);
                    board[i][j] = 0;
					if(tempScore > score)
					{
						score = tempScore;
						moverow = i;
						movecol = j;
					}
				}
			}
		}
		
		board[moverow][movecol] = 2;
		
		p2 -> move[0] = row_char(moverow);
		p2 -> move[1] = col_char(movecol);
	
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				p2->board[i][j] = board[i][j];
			}
		}
		
		AppendPlaySnapshot(l, p2);
		PrintPlayList(l);
		
		print_fun(board,p1,p2);
		win_flag = IsWin(board);

		if(win_flag == 0)
		{
			printf("Take back move? y/n: ");
			char takeback;
			scanf(" %c", &takeback);
			switch(takeback)
			{
				case 'y':
					TakeBack(board,l);
					print_fun(board,p1,p2);
					continue;
				default:
					if(count == 0)
					{
						RemoveFirstPlay(l);
					}
					count++;
					break;
			}
		}

		if(win_flag == 2)
		{
			printf("AI won. Take back move? y/n: ");
			char takeback = 'y';
			scanf(" %c", &takeback);
			switch(takeback)
			{
				case 'y':
					TakeBack(board,l);
					print_fun(board,p1,p2);
					continue;
				default:
					break;
			}
		}
		
		if(win_flag != 0)
		{
			if (win_flag == 1)
			{
				printf("Player 1 wins! Game Over!\n\n");
			}
			else if (win_flag == 2)
			{
				printf("AI wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
		else if (is_there_empty_cell(board)==0)
			break;
	}
	if (tie==1)
	{
		printf("The game is a tie!\n");
	}
	DeletePlay(d);
}

