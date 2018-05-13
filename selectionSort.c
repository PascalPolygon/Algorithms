#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void swap(int *x, int *y);
void linking(int newData);
void printList(void);
void sortList(void);


struct LIST
{
	int value;
	struct LIST * next;
	struct LIST * prev;
};

struct LIST *headNode = NULL;
void swap_list(struct LIST *tempNode, struct LIST *min);

int main(void)
{
	srand(time(NULL));
	int n = 10;
	int a[10];
	int i = 0, j = 0;
	int min_index;
	int number;

	printf("Random number generation:\n");

	for (i = 0; i < n; i++)
	{
		number = rand() % 100;
		a[i] = number;
		printf("%d ", a[i]);
		linking(number);
	}
	printf("\n");

	for (j = 0; j < n - 1; j++)
	{
		min_index=j;

		for (i = j + 1; i < n; i++)
		{
			if (a[i] < a[min_index])
				min_index = i;
		}

		if (min_index != j)
			swap(&a[j], &a[min_index]);
	}

	printf("Sorted array:\n");
	for (i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");

	sortList();

	printf("Sorted linked list:\n");
	printList();

	return 0;
}

void swap(int *x, int *y)
{
	*x = (*x + *y);
	*y = *x - *y;
	*x = *x - *y;
}

void linking(int newData)
{
	struct LIST *newNode, *tempNode;

	newNode = (struct LIST*)malloc(sizeof(struct LIST));
	newNode->value = newData;
	newNode->next = NULL;


	if (headNode == NULL)
	{
		headNode = newNode;
		headNode->prev = NULL;
	}

	else
	{
		tempNode = headNode;
		while (tempNode->next != NULL)
		{
			//tempNode->prev = tempNode;   //following node pointed to by tempNode-> prev
			tempNode = tempNode->next;
		}

		tempNode->next = newNode;
		newNode->prev = tempNode;
		newNode->next = NULL;
	}
	return;
}

void printList(void)
{
	struct LIST *tempNode, *last;

	if (headNode != NULL)
	{
		tempNode = headNode;
		while (tempNode != NULL)
		{
			printf("%d ", tempNode->value);
			last = tempNode;
			tempNode = tempNode->next;
		}
		printf("\n");
		while (last != NULL)
		{
			printf("%d ", last->value);
			last = last->prev;
		}
		printf("\n");
	}
}

void sortList(void)
{
	struct LIST *tempNode, *current, *min, *next, *prev, *temp;
	int min_val;

	if (headNode != NULL)
	{
		tempNode = headNode;
		min = headNode;

		while (min->next != NULL)
		{
			//printf("In while\n");
			tempNode = min;
			//printf("New temp: %d\n", tempNode->value);
			min_val = tempNode->value;
			current = tempNode->next;

			while (current != NULL)
			{
				
				if (current->value < min_val)
				{
					//printf("Inner while: %d\n", current->value);
					min_val = current->value;
					min = current;
					//min->next = current->next;
					//min->prev = current->prev;
					//break;
				}
				current = current->next;
			}
			//printf("\t****IN HERE !!!!! *****\n");
			//printf("minimum: %d\n", min_val);
			if (min_val<tempNode->value)
			{    
				swap_list(tempNode, min);
				//printList();
			}
			min = min->next;
			//tempNode = tempNode->next;
			//printf("next: %d\n", tempNode->value);
		}
	}
}

void swap_list(struct LIST *tempNode, struct LIST *min)
{
	struct LIST  *tempNode_1, *tempNode_2, *prev, *next, *prev2, *next2;

	/*if (headNode != NULL)
	{
		tempNode_1 = headNode;

		while (tempNode_1->value != x)
			tempNode_1 = tempNode_1->next;
	}
	if (headNode != NULL)
	{
		tempNode_2 = headNode;

		while (tempNode_2->value != y)
			tempNode_2 = tempNode_2->next;
	}*/
	tempNode_1 = tempNode;
	tempNode_2 = min;
	//printf("Just out!\n");
	if (tempNode_1->next != tempNode_2 && tempNode_2->next != tempNode_1 && tempNode_2->next != NULL && tempNode_1->prev != NULL)
	{
		//printf("If\n");
		prev = tempNode_1->prev;
		next = tempNode_1->next;
		prev2 = tempNode_2->prev;
		next2 = tempNode_2->next;

		prev->next = tempNode_2;
		tempNode_2->next = next;
		prev2->next = tempNode_1;
		tempNode_1->next = next2;

		next->prev = tempNode_2;
		tempNode_2->prev = prev;
		next2->prev = tempNode_1;
		tempNode_1->prev = prev2;
	}
	else if (tempNode_1->next == tempNode_2)
	{
		//printf("In else if\n");

		if (tempNode_2->next == NULL)
		{
			next = NULL;
			prev = tempNode_1->prev;
		}

		else if (tempNode_1->prev == NULL)
		{
			prev = NULL;
			next = tempNode_2->next;
		}
		else
		{
			prev = tempNode_1->prev;
			next = tempNode_2->next;
		}

		if (prev == NULL)
			headNode = tempNode_2;
		else
			prev->next = tempNode_2;

		tempNode_2->next = tempNode_1;
		tempNode_1->next = next;

		if (next != NULL)
			next->prev = tempNode_1;

		tempNode_1->prev = tempNode_2;
		tempNode_2->prev = prev;
	}
	else if (tempNode_2->next == NULL && tempNode_1->prev != NULL)
	{
		//printf("Other If\n");
		prev = tempNode_1->prev;
		next = tempNode_1->next;
		prev2 = tempNode_2->prev;
		next2 = NULL;

		prev->next = tempNode_2;
		tempNode_2->next = next;
		prev2->next = tempNode_1;
		tempNode_1->next = NULL;

		next->prev = tempNode_2;
		tempNode_2->prev = prev;
		//next2->prev = tempNode_1;
		tempNode_1->prev = prev2;
	}
	else if (tempNode_1->prev == NULL && tempNode_2->next != NULL)
	{
		//printf("Last\n");
		//prev = NULL;
		next = tempNode_1->next;
		prev2 = tempNode_2->prev;
		next2 = tempNode_2->next;
		//temp = tempNode_1;

		//tempNode_2 = temp;
		headNode = tempNode_2;
		next->prev = tempNode_2;
		tempNode_2->next = next;
		tempNode_2->prev = NULL;
		tempNode_1->next = next2;
		prev2->next = tempNode_1;
		next2->prev = tempNode_1;
		tempNode_1->prev = prev2;
	}
	else if (tempNode_1->prev == NULL && tempNode_2->next == NULL)
	{
		//printf("First and last\n");
		prev = NULL;
		next = tempNode_1->next;
		prev2 = tempNode_2->prev;
		next2 = NULL;

		headNode = tempNode_2;
		next->prev = tempNode_2;
		tempNode_2->next = next;
		tempNode_2->prev = prev;

		tempNode_1->next = next2;
		prev2->next = tempNode_1;
		tempNode_1->prev = prev2;
	}

}
	

