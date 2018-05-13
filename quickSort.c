#include <stdio.h>

void quicksort(int array[10], int start, int end);
int partition(int array[10], int left, int right);
void swap(int *x, int *y);

int main(void)
{
	int array[10], i;
	
	printf("Enter an array of size 10\n");
	
	for (i = 0; i < 10; i++)
	{
		scanf("%d", &array[i]);
	}
	
	quicksort(array, 0, 9);
	
	printf("Printing Sorted array...\n");

	for (i = 0; i < 10; i++)
	{
		printf("%d ", array[i]);
	}
	
	return 0;
}

void quicksort(int array[10], int start, int end)
{
	int p;
	
	if (start < end)
	{
		p = partition(array, start, end);
		quicksort(array, start, p-1);
		quicksort(array, p+1, end);
	}
}

int partition(int array[10], int left, int right)
{
	int i = left;
	int j = left;
	int pivot = array[right];
	
	//printf("In partition\n");
	for (j = left; j <= right-1; j++)
	{
		if (array[j] <= pivot)
		{
			swap(&array[i], &array[j]);
			i++;
		}
	}
	swap(&array[i], &array[right]);
	
	return (i);
}

void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}