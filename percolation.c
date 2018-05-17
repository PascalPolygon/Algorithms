#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
* Author: Mawaba Pascal Dao, pdao2015@my.fit.edu
* Course: CSE 1002, Section 05, Spring 2018
* Project: Percolation
SORRY FOR LATE SUBMISSION, I HAD TO TAKE CARE OF FAMILY STUFF
*/

void open_site(int size, char board[size][size], int x, int y);                                    //Opens randomly selected site
void print_board(int size, char board[size][size]);
int check_path_way(int size, char board[size][size]);                                              //Makes sure there is a leat one open site on each row before attemting percolation
int percolate(int size, char board[size][size], char board_2[size][size]);

int main(int argc, char *argv[])
{
	srand(time(NULL));

	int size, iterations, i, j,l,x, y, can_percolate = 0, through = 0, fraction = 0;
	double treshold = 0.0;
	size = atoi(argv[1]);
	iterations = atoi(argv[2]);

	char grid[size][size];                                                                         //Original grid
	char board_2[size][size];																	   //updated board after percolation

	for (l = 0; l < iterations; l++)
	{
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				grid[i][j] = '-';
			}

		}

		do
		{
			x = rand() % size;                                                                     //Randomly genenate x and y coordinates for site to open
			y = rand() % size;
			open_site(size, grid, x, y);
			can_percolate = check_path_way(size, grid);
		} while (can_percolate != 1);                                                              //Only attempts percolation when path is plausible

		through = percolate(size, grid, board_2);


		fraction = 0;
		while (through != 1)
		{
			x = rand() % size;
			y = rand() % size;
			open_site(size, grid, x, y);
			through = percolate(size, grid, board_2);                                              //Attempts percolation until successful (i.e: through == 1)
		} 

		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				if (board_2[i][j] == '+')
					fraction++;
			}
		}

		treshold += (double)fraction / (size*size);
	}
	
	treshold /= iterations;

	printf("The treshold is: %2.1lf\n", treshold);
	printf("The last final grid is:\n");
	print_board(size, board_2);

	return 0;
}

void open_site(int size, char board[size][size], int x, int y)
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (i == x && j == y)
				board[i][j] = ' ';
				
		}
	}
}

void print_board(int size, char board[size][size])
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		printf("|");
		for (j = 0; j < size; j++)
			printf("%c|", board[i][j]);
		printf("\n");
	}
}

int check_path_way(int size, char board[size][size])
{
	int i = 0, open = 0, pathway, j, flag = 0;
	
	while (i < size)
	{
		for (j = 0; j < size; j++)
		{
			if (board[i][j] == ' ')
			{
				open++;
				i++;
				break;                                                                             //Finds first open site on each row and goes to the next row
			}
			else if (j == (size - 1) && board[i][j] != ' ')
				i++;
		}
	}
	
	pathway = (open == size) ? 1 : 0;                                                              //Path to percolation is achievale (pathway ==1) when there is at least one open site on each row

	return pathway;
	
}

int percolate(int size, char board[size][size], char board_2[size][size])
{
	int i = 0, j = 0, l = 0, row = 0, spots[size], spots1[size], little_drip[size];
	int turkeyTimeBomb = 1, through = 0;

	int num = 0;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			board_2[i][j] = board[i][j];                                                           //Make copy of original grid
		}

	}


	for (j = 0; j < size; j++)
	{
		if (board[row][j] == ' ')
		{
			board_2[row][j] = '+';                                                                 //Percolate all open sites on first row
		}

	}

	while (turkeyTimeBomb == 1)
	{
		l = 0;
		row++;
		little_drip[0] = -1;
		for (j = 0; j < size; j++)
		{
			if (board[row][j] == ' ' && board_2[row - 1][j] == '+')
			{
				little_drip[l] = j;                                                                //If perolation top row shares at least one column with the row underneath, substance percolates through, to the row underneath
				board_2[row][j] = '+';
				l++;
			}

		}

		if (little_drip[0] > -1)                                                                   //When substance can percolate to follwing row
		{
			for (i = 0; i < l; i++)
			{
				j = little_drip[i] - 1;

				while (j > -1 && board[row][j] == ' ')                                             //From open postion to col 0, percolate when possible
				{
					board_2[row][j] = '+';
					j--;
				}

				j = little_drip[i] + 1;

				while (j < size  && board[row][j] == ' ')                                          //From open postion to last col, percolate when possible
				{
					board_2[row][j] = '+';
					j++;
				}

				if (row == (size - 1))
				{
					through = 1;                                                                   //Percolation is through when +'s reaced the bottom row
					turkeyTimeBomb = 0;
				}
				else
					turkeyTimeBomb = 1;
			}
		}
		else
			turkeyTimeBomb = 0;
	}

	return through;
}

			