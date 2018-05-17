 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 //#include <conio.h>
 
/* 
 * Author: Mawaba Pascal Dao, pdao2015@my.fit.edu
 * Course: CSE 1002, Section 05, Spring 2018 
 * Project: game-of-life-1
 */
 

 void new_era(int world_size, int world[world_size][world_size], int cycles);        //Updates current world
 int event_horizon(int i, int j, int world_size, int world[world_size][world_size]); //Checks limits of the matrix, and current position
 int pulse(int place, int state, int neighbor);	 									//Checks cell pulse (dead or alive)
 void graphics(int world_size, int world[world_size][world_size]); 
 
 int main(int argc, char *argv[])
 {
	char firstLine[100];
	int i,size=0;
	int iterations = atoi(argv[2]);

	FILE *infile;
	infile = fopen(argv[1],"r");
	
	

	fscanf(infile, "%[^\n]s", firstLine);      //Reads first line in file to be used to determine matrix size
	
	fclose(infile);
	
	for (i = 0; i < strlen(firstLine); i++)    
	{
		if (firstLine[i] == ';')			 
		{
			size++;                                
		}
	}
	size+=1;                                   //Number of columns is number of semi colons plus one

								
	int world[size][size];					  //square matrix, therefore columns equal rows
	int j=0,k=0,l=0;
	i=0;

	char c;
	
	fclose(infile);	                         //Close an reopen file to start reading from beginning
	infile = fopen(argv[1],"r");
	
do
{
	c = fgetc(infile);						//Reads charachter by charachter...
	if (c!=';')								 // Avoiding semi colons 	
	{
		world[k][l]=c-'0';                   //Stores charachter as integers in integer matrix
		if (l == (size))
		{
			l = 0;
			k+=1;
		}
		else
		{
			l++;
		}
	}
}while(c!=EOF);                             //Reads until end of file

fclose(infile);

new_era(size,world,iterations);             //Function call to update matrix


/*printf("The final position: \n");

for (i = 0; i < size; i++)
{
	for (j = 0; j< size; j++)
	{
		if (world[i][j]==1)
		{
			printf("%d %d\n", i, j);     
		}
	}
}*/

//graphics(size, world);
 
FILE *outfile;                             //Initializing output file
outfile = fopen("output_test.csv","w");       

for (i = 0; i < size; i++)
{
	for (j = 0; j< size; j++)
	{
		if (j == (size-1))
			fprintf(outfile, "%d",world[i][j]);
		else
			fprintf(outfile, "%d;",world[i][j]);
	}
	fprintf(outfile,"\n");
}
fclose(outfile);

	return 0;
 }


 
 void new_era(int world_size, int world[world_size][world_size],  int cycles)
 {
	 int i, j, k, place,neighbor=0;

	 int new_world[world_size][world_size];
	 
	 for (k = 1; k <= cycles; k++)
	 {
		system("clear");
		for (i=0; i < world_size; i++)
	 	{
			for (j=0; j < world_size;j++)
		 	{
			 	new_world[i][j] = 0;
				place = event_horizon(i,j,world_size,world);      //function call to check current position on the matrix

				if (place == 1)                                   //Determines cells to check given a condition 
				{												 //9 total relevant position were determined, bottom, top, left and right sides, four corners, and interior	
					if (world[i][j+1]==1)						//The relevant position determine which neighbouring cells to check for pulse
						neighbor++;
					if (world[i+1][j]==1)
						neighbor++;
					if (world[i+1][j+1]==1)
						neighbor++;
				
					new_world[i][j]=pulse(place, world[i][j], neighbor);   //updates new matrix
				
					neighbor = 0; 
				}
				
				else if(place == 2)
				{
					if (world[i][j-1]==1)
						neighbor++;
					if (world[i+1][j]==1)
						neighbor++;
					if (world[i+1][j-1]==1)
						neighbor++;
				
					new_world[i][j]=pulse(place, world[i][j], neighbor);
				
					neighbor = 0; 
				}

				else if(place == 3)
				{
					if (world[i][j+1]==1)
						neighbor++;
					if (world[i][j-1]==1)
						neighbor++;
					if (world[i-1][j]==1)
						neighbor++;
					if (world[i+1][j+1]==1)	
						neighbor++;
					if (world[i+1][j-1]==1)
						neighbor++;

					world[i][j]=pulse(place, world[i][j], neighbor);

					neighbor = 0; 
				}

				else if (place == 4)
				{
					if (world[i][j+1]==1)
						neighbor++;
					if (world[i-1][j+1]==1)
						neighbor++;
					if (world[i-1][j]==1)
						neighbor++;

					new_world[i][j]=pulse(place, world[i][j], neighbor);

					neighbor = 0; 
				}

				else if (place == 5)
				{
					if (world[i][j-1]==1)
						neighbor++;
					if (world[i-1][j-1]==1)
						neighbor++;
					if (world[i-1][j]==1)
						neighbor++;
					
					new_world[i][j]=pulse(place, world[i][j], neighbor);

					neighbor = 0; 
				}

				else if (place == 6)
				{
					if (world[i][j+1]==1)
						neighbor++;
					if (world[i][j-1]==1)
						neighbor++;
					if (world[i-1][j]==1)
						neighbor++;
					if (world[i-1][j+1]==1)	
						neighbor++;
					if (world[i-1][j-1]==1)
						neighbor++;
					
					new_world[i][j]=pulse(place, world[i][j], neighbor);

					neighbor = 0; 
				}

				else if (place == 7)
				{
					if (world[i+1][j]==1)
						neighbor++;
					if (world[i-1][j]==1)
						neighbor++;
					if (world[i][j+1]==1)
						neighbor++;
					if (world[i-1][j+1]==1)	
						neighbor++;
					if (world[i+1][j+1]==1)
						neighbor++;
					
					new_world[i][j]=pulse(place, world[i][j], neighbor);

					neighbor = 0; 
				}

				else if (place == 8)
				{
					if (world[i+1][j]==1)
						neighbor++;
					if (world[i-1][j]==1)
						neighbor++;
					if (world[i][j-1]==1)
						neighbor++;
					if (world[i-1][j-1]==1)	
						neighbor++;
					if (world[i+1][j-1]==1)
						neighbor++;
					
					new_world[i][j]=pulse(place, world[i][j], neighbor);

					neighbor = 0; 
				}

				else if (place == 0)
				{
					if (world[i+1][j]==1)
						neighbor++;
					if (world[i-1][j]==1)
						neighbor++;
					if (world[i][j-1]==1)
						neighbor++;
					if (world[i][j+1]==1)	
						neighbor++;
					if (world[i+1][j-1]==1)
						neighbor++;
					if (world[i+1][j+1]==1)
						neighbor++;	
					if (world[i-1][j-1]==1)
						neighbor++;
					if (world[i-1][j+1]==1)
						neighbor++;	
				
					
					new_world[i][j]=pulse(place, world[i][j], neighbor);

					neighbor = 0; 
				}

		 	}
	 	}

		for (i=0; i < world_size; i++)
	 	{
			for (j=0; j < world_size;j++)
		 	{
			 	world[i][j]=new_world[i][j];
		 	}
	 	}
		printf("iteration %d\n", k);
		graphics(world_size, world);
		//system("clear");
	}

	
 }
 
  int event_horizon(int i, int j, int world_size, int world[world_size][world_size])
  {
	  if (i == 0)                                    // Identifying place on matrix and assighing one of 9 relevent position
	  {
		  if (j == 0)
			  return 1;
		  else if (j == (world_size-1))
			  return 2;
		  else 
			  return 3;
	  }
	  else if(i == (world_size-1))
	  {
		  if (j == 0)
			  return 4;
		  else if (j == (world_size-1))
			  return 5;
		  else
			  return 6;
	  }
	  else if (j == 0)
		  return 7;
	  else if (j == (world_size-1))
		  return 8;
	  else 
		  return 0;
  }

  int pulse(int place, int state, int neighbor)           //Given current state, fuction applies game rules and determines new state of sell (dead or alive)
  {
	int pulse;                                     

	if (neighbor < 2 && state==1)
	{
		pulse=0;
	}
	else if(neighbor > 3 && state==1)
	{
		pulse=0;
	}	
	else if((neighbor == 2 || neighbor ==3) && state==1)
	{
		pulse=1;
	}
	else if(neighbor == 3 && state==0)
	{
		pulse=1;
	}

	return pulse;
  }
  
   void graphics(int world_size, int world[world_size][world_size])
   {
	   int i = 0, j = 0;
	   for (i=0; i < world_size; i++)
	   {
		   for (j=0; j < world_size; j++)
		   {
				if (world[i][j] == 1)
					printf("|o");
				else
					printf("| ");
		   }
		   printf("|\n");
	   }
   }
  
 
 
 
	