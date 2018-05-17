#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void addv(int newData);
void addi(int newData, int index);
void delv(int oldData);
void deli(int index);
void printList(void);
void revs();
void addi(int newData, int index);
void linking(int newData);

typedef char STRING[10];

struct LIST
{
	int value;
	struct LIST * next;
	struct LIST * prev;
};

struct LIST *headNode = NULL;
struct LIST *tailNode = NULL;

int main(void)
{
	STRING instruction;

	int userNum;
	int data;
	int index;
	int newData; 
	int i = 0;

	printf("Size of list: ");
	scanf("%d", &userNum);

	clock_t tic = clock();
	for (i = 0; i < userNum; i++)
		linking(i);
	clock_t toc = clock();
	printf("Operation time: %.20f\n", (double)(toc - tic) / (CLOCKS_PER_SEC));
	//printList();
	printf("Feed the precious instructions\n");

	scanf("%s", instruction);

	while (strcmp(instruction, "end") != 0)
	{
		if (strcmp(instruction, "addv") == 0)
		{
			scanf("%d", &data);
			clock_t debut = clock();
			addv(data);
			clock_t fin = clock();
			printf("Operation time: %.20f\n", (double)(fin - debut) / (CLOCKS_PER_SEC));
			//printList();
		}
		else if (strcmp(instruction, "addi") == 0)
		{
			scanf("%d %d", &newData, &index);
			addi(newData, index);
			//printList();
		}
		else if (strcmp(instruction, "delv") == 0)
		{
			scanf("%d", &newData);
			clock_t tip = clock();
			delv(newData);
			clock_t top = clock();
			printf("Operation time: %.20f\n", (double)(top - tip) / (CLOCKS_PER_SEC));
			//printList();
		}
		else if (strcmp(instruction, "deli") == 0)
		{
			scanf("%d", &index);
			clock_t begin = clock();
			deli(index);
			clock_t end = clock();
			printf("Operation time: %.20f\n", (double)(end - begin) / (CLOCKS_PER_SEC));
			//printList();
		}
		else if (strcmp(instruction, "revs") == 0)
		{
			clock_t now = clock();
			revs();
			clock_t then = clock();
			printf("Operation time: %.20f\n", (double)(then - now) / (CLOCKS_PER_SEC));
			//printList();
		}
		else
			printList();

		scanf("%s", instruction);
	}

	return 0;
}

void addv(int newData)
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

void addi(int newData, int index)
{
	struct LIST *newNode, *tempNode, *next;
	int i = 0;

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

		while (i != (index-1) && tempNode->next != NULL)
		{
			tempNode = tempNode->next;
			i++;
		}
		if (i == (index-1) && tempNode->next!=NULL)
		{
			newNode->next = tempNode->next;
			next = tempNode->next;
			tempNode->next = newNode;
			newNode->prev = tempNode;
			next->prev = newNode;
		}
		else
		{
			tempNode->next = newNode;
			newNode->prev = tempNode;
		}
	}
	return;
}

void printList(void)
{
	struct LIST *tempNode, *last;
	printf("Printing...\n");
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

void delv(int oldData)
{
	struct LIST  *tempNode, *shadowNode = NULL, *next;
	int i = 0;

	if (headNode != NULL)
	{
		tempNode = headNode;

		while (tempNode->value != oldData && tempNode->next != NULL)
		{
			shadowNode = tempNode;
			tempNode = tempNode->next;
			//i++;
		}
		if (tempNode->value == oldData && shadowNode != NULL && tempNode->next != NULL)
		{
			printf("Deleted: %d\n", tempNode->value);
			free(tempNode);
			shadowNode = tempNode->prev;
			shadowNode->next = tempNode->next;
			next = tempNode->next;
			next->prev = shadowNode;
			tempNode = NULL;
			
		}
		else if (tempNode->value == oldData && tempNode->next == NULL )
		{
			//printf("Else if\n");
			printf("Deleted: %d\n", tempNode->value);
			free(tempNode);
			shadowNode = tempNode->prev;
			tempNode = NULL;
			shadowNode->next = NULL;
			/*next = tempNode->next;
			next->prev = shadowNode;
			tempNode = NULL;*/
		}
		else if (shadowNode == NULL)
		{
			free(headNode);
			headNode = tempNode->next;
			headNode->prev = NULL;
			tempNode = NULL;
		}
	}
	return;
}

void deli(int index)
{
	struct LIST *tempNode, *shadowNode = NULL, *next;
	int i = 0;

	if (headNode != NULL)
	{
		tempNode = headNode;

		while (i != index && tempNode->next != NULL)
		{
			shadowNode = tempNode;
			tempNode = tempNode->next;
			i++;
		}
		if (i == (index) && shadowNode != NULL && tempNode->next != NULL)
		{
			free(tempNode);
			shadowNode = tempNode->prev;
			shadowNode->next = tempNode->next;
			next = tempNode->next;
			next->prev = shadowNode;
			tempNode = NULL;
		}
		else if (i == index && tempNode->next == NULL)
		{
			//printf("Else if\n");
			free(tempNode);
			shadowNode = tempNode->prev;
			tempNode = NULL;
			shadowNode->next = NULL;
			/*next = tempNode->next;
			next->prev = shadowNode;
			tempNode = NULL;*/
		}
		else if (shadowNode == NULL)
		{
			free(headNode);
			headNode = tempNode->next;
			headNode->prev = NULL;
			tempNode = NULL;
		}
	}
}

void revs()
{
	struct LIST *prev = NULL; // Previous pointer set to NULL (before head)
	struct LIST *current = headNode; //Current Node initialized to head Node 
	struct LIST *next = NULL; //Next node

	while (current != NULL) // Iterating  until current Node is at the end of list
	{
		prev = current->prev;
		next = current->next; //store address of next node
		current->next = prev; // Next field in node points at previous node (reverse)
		current->prev = next;
		//prev = current; //move prev to following node
		current = next; //move current to next node 
	}
	headNode = prev->prev; //Head points to first node in reserved list
}

void linking(int newData)
{
	struct LIST *newNode, *tempNode, *next;

	newNode = (struct LIST*)malloc(sizeof(struct LIST));
	newNode->value = newData;
	newNode->next = NULL;


	if (headNode == NULL)
	{
		headNode = newNode;
		tailNode = newNode;
		tailNode->prev = NULL;
		tailNode->next = NULL;
	}
	else
	{
		tailNode->next = newNode;
		newNode->prev = tailNode;
		tailNode = newNode;
		tailNode->next = NULL;
	}
	return;
}