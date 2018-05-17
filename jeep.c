/*
* Author:  Mawaba Dao, pdao2015@my.fit.edu
* Course:  CSE 1002, Section 05, Fall 2018
* Project: JEEP
*/

#include <stdio.h>

double distance(int n, double cap, double rate);

int main(void)
{
	int n = 1, j = 0, i = 1;
	double cap, rate, position=0;
	scanf("%d", &n);
	
	while(n!=0)
	{
		scanf("%lf %lf", &cap, &rate);
		position = distance(n, cap, rate);
		j++;
		printf("%d. Distance is %5.2lf kilometers\n", j, position);
		scanf("%d", &n);
	}

	
	return 0;
}

double distance(int n, double cap, double rate)
{
	if (n == 1|| n == 2)
		return  n*(cap * (100 / rate));
	else
		return (cap*(100 / rate)/(2*n-3) + distance((n-1), cap, rate));

}