#include <stdio.h>

typedef int bool;
#define true 1
#define false 0

void i_am_your_queen_now(int row, int col, int size, int board[size][size]);
int is_it_safe_now(int row, int size, int board[size][size], int spots[size]);
int no_throne(int thrones, int j, int spots[thrones], int size, int board[size][size], int row, int row_min);
int solve(int row_min, int n, int board[n][n]);


int solve(int row_min, int n, int board[n][n])
{
	printf("Inside solve\n");
	int spots[n];
	int i = row_min, j, thrones, k, m;

	while(i < n )//&& i >= row_min) 
	{
		printf("Inside loop\n");
		j = 0;
		thrones = is_it_safe_now(i, n, board, spots);
		if (thrones > 0)
			i_am_your_queen_now(i, spots[j], n, board);
		else if (thrones == 0)
		{
	
			i = no_throne(thrones, j, spots, n, board, i, row_min);
			if (i == 0)
				return 0;
		}
		printf("rows: %d\n", i);
		i++;

		for (k = 0; k < n; k++)
		{
			for (m = 0; m < n; m++)
			{
				printf("%4d", board[k][m]);
			}
			printf("\n");
		}
	}
	printf("Final row: %d\n", i);
	if (i == n)
		return 1;
	/*else if (i < row_min)
		return 0;*/
}

int is_it_safe_now(int row, int size, int board[size][size], int spots[size])
{
	printf("Getting kicked out here\n");
	int i, thrones = 0;

	for (i = 0; i < size; i++)
	{
		if (board[row][i] == 0)
		{
			spots[thrones] = i;
			thrones++;
		}
	}

	printf("\n Thrones: %d\n", thrones);
	return thrones;
}

void i_am_your_queen_now(int row, int col, int size, int board[size][size])
{
	int i, j;

	board[row][col] = 10;

	for (i = row+1; i < size; i++)
		board[i][col] = (board[i][col]==0)? (row+1): board[i][col];

	i = row + 1;
	j = col + 1;

	while (j < size && i < size)
	{
		board[i][j] = (board[i][j]==0)? (row+1): board[i][j];
		i++;
		j++;
	}
	i = row + 1;
	j = col - 1;
	while (i < size && j >= 0)
	{
		board[i][j] = (board[i][j] == 0) ? (row + 1) : board[i][j];
		i++;
		j--;
	}

}

int no_throne(int thrones, int j, int spots[thrones], int size, int board[size][size], int row, int row_min)
{
	printf("No thrones\n");
	int i = 0, l = 0, var=size+2;
	bool turkeyTimeBomb=true; 
	while (turkeyTimeBomb)
	{
		row-=1;
		if (row < row_min)
		{
			printf("Reached row: %d\n", row);
			return 0;
		}
	
		thrones = is_it_safe_now(row, size, board, spots);
		//board[row][spots[j]] = 0;
		//var = j;
		//j++;
		printf("j : %d index: %d\n", j, spots[j]);
		if ((j+1) <=thrones)
		{
			//printf("j : %d index: %d\n", j, spots[j]);
			//board[row][spots[j]] = -1;
			for (i = 0; i < size; i++)
			{
				if (board[row][i]==10 && i!=spots[j])
					board[row][i]=-1;
			}
			//j++;
			for (i = (row + 1); i < size; i++)
			{
				for (l = 0; l < size; l++)
				{
					if (board[i][l] >= (row + 1))
						board[i][l] = 0;
				}
			}
			printf("New queen at index: %d\n", spots[j]);
			for (i = 0; i < thrones; i++)
				printf("%d ", spots[i]);
			printf("\n");
			i_am_your_queen_now(row, spots[j], size, board);
			//j++;
			turkeyTimeBomb = false;
		}
		else if (j > thrones || thrones == 0)
		{
			for (i = 0; i < size; i++)
			{
				if (board[row][i] == -1)
					board[row][i] = 0;
			}
			j = 0;
			turkeyTimeBomb = true;
		}
			
	}
		
	return row;
	
		//return no_throne(thrones, j, spots, size, board, row-1)
}



int main(void)
{
	int i = 0, j = 0, l = 0, n = 1, m = 1, input[1000][2], thrones, k;
	bool turkeyTimeBomb = true;
	int solutions = 0;

	scanf("%d %d", &n, &m);
	printf("Hello\n");
	while(turkeyTimeBomb)
	{
		solutions = 0;
		printf("Here\n");
		int board[n][n];
		//int spots[n];
		//int var = size + 2;
		
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				board[i][j] = 0;
			}
		}
		
		for (i = 1; i <=m; i++)
		{
			printf("reading\n");
			scanf("%d %d", &input[i][0], &input[i][1]);
			board[(input[i][0])][(input[i][1])] = -1;
		}
		
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				printf("%d", board[i][j]);
			}
			printf("\n");
		}

		printf("\n\n");
		i = 0;
		j = 0;
		i_am_your_queen_now(i, j, n, board);

		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				printf("%2d", board[i][j]);
			}
			printf("\n");
		}

		i = 0;
		j = 0;
		i++;

		solutions += solve(i, n, board);
		printf("****************************SOLUTIONS: %d\n", solutions);
		int p;

		
			for (i = (n - 1); i >= 0; i--)
			{
				//printf("Solutions: %d\n", solutions);
				for (j = 0; j < n; j++)
				{
					if (board[i][j] == 0)
					{
						for (k = 0; k < n; k++)
							board[i][k] = (board[i][k] == 10) ? -1 : board[i][k];
						for (k = (i + 1); k < n; k++)
						{
							for (l = 0; l < n; l++)
							{
								if (board[k][l] >= (i + 1))
									board[k][l] = 0;
							}
						}
						i_am_your_queen_now(i, j, n, board);
						printf("Spot at: %d, %d\n", i,j);
						i++;
						solutions += solve(i, n, board);
						printf("****************************SOLUTIONS: %d\n", solutions);
						for (i = 0; i < n; i++)
						{
							for (j = 0; j < n; j++)
							{
								printf("%4d", board[i][j]);
							}
							printf("\n");
						}
						//return 0;
						//solutions += solve(i, n, board);
						//return 0;
						//j = n + 2;
					}
					
				}
				//i = (j == n + 2) ? -2 : i;
			}
		

		/*for (i = (n-1); i >= 0; i--)
		{
			//printf("Solutions: %d\n", solutions);
			for (j = 0; j < n; j++)
			{
				if (board[i][j] == 0)
				{
					for (k = (i + 1); k < n; k++)
					{
						for (l = 0; l < n; l++)
						{
							if (board[k][l] >= (i + 1))
								board[k][l] = 0;
						}
					}
					i_am_your_queen_now(i, j, n, board);
					solutions += solve(i, n, board);
				}
			}
		}*/
		printf("Solutions: %d\n", solutions);

		printf("\n\n");
		int k, m;


		printf("\n\n");

		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				printf("%4d", board[i][j]);
			}
			printf("\n");
		}

		
		/*for (j = 0; j < m; j++)
		{
			for (l = 0; l < 2; l++)
			{
				printf("%d ", input[j][l]);
			}
			printf("\n");
		}*/
		
		printf("New board\n");
		scanf("%d %d", &n, &m);
	
		if (n == 0 && m == 0)
		{
			turkeyTimeBomb = false;
		}
	}
	
	
	return 0;
}


/*while(turkeyTimeBomb)
{
scanf("%d %d", &n, &m);
//printf("%d %d\n", n, m);
input[j][0] = n;
input[j][1] = m;
j++;

if (n == 0 && m == 0)
{
turkeyTimeBomb = false;
}

}

for (i = 0; i < (j-1); i++)
{
for (l = 0; l < 2; l++)
{
printf("%d ", input[i][l]);
}
printf("\n");
}*/


/*while (i < n)
{
printf("Inside loop\n");
j = 0;
thrones = is_it_safe_now(i, n, board, spots);
if (thrones > 0)
i_am_your_queen_now(i, spots[j], n, board);
else if (thrones == 0)
{
i = no_throne(thrones, j, spots, n, board, i);
}
printf("rows: %d\n", i);
i++;

for (k = 0; k < n;k++)
{
for (m = 0; m < n; m++)
{
printf("%4d", board[k][m]);
}
printf("\n");
}
}*/