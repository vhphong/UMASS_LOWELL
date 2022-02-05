#include <stdio.h>
#include <stdlib.h>

enum status { FAILURE, SUCCESS };
typedef enum status Status;

enum boolean { FALSE, TRUE };
typedef enum boolean Boolean;

typedef void* STACK;

struct node;
typedef struct node Node;
struct node
{
	char data;
	Node *next;
};
struct stack
{
	Node* head;
};
typedef struct stack Stack;
typedef Stack* Stackptr;

STACK stack_init_default(void);

Status stack_push(STACK hStack, char item);

Status stack_pop(STACK hStack);

char stack_top(STACK hStack, Status* pStatus);


Boolean wordcompare(STACK hStack, char word[]);

void stack_destroy(STACK* phStack);

Boolean stack_empty(STACK hStack);

void clear_keyboard_buffer(void);

int main(int argc, char* argv[])
{
 	
	int num,i;
	scanf("%d",&num);
	clear_keyboard_buffer();
	STACK hStack[num];
	Boolean result[num];
	char word[128];
	for( i = 0; i < num ; i++)
	{	
		
		hStack[i] = NULL;
		hStack[i] = stack_init_default();
		if(hStack[i] == NULL)
		{
			printf("Fail to allocate memory\n");
			exit(1);
		}
		fgets(word,128,stdin);
		if(word[0] == '\n')
			result[i] = TRUE;
		else
			result[i] =  wordcompare(hStack[i],word);
		word[0] = '\0';
	}
	for( i = 0; i < num; i++)
	{
		if (result[i] == TRUE)
		{
			printf("Yes\n");
		}
		else if (result[i] == FALSE)
		{
			printf("No\n");
		}
	}
	for( i = 0; i < num; i++)
	{
		stack_destroy(&hStack[i]);
	}		
	return 0;		
}


STACK stack_init_default(void)
{
	Stackptr pStack;
	pStack = (Stackptr)malloc(sizeof(Stack));
	if (pStack != NULL)
	{
		pStack->head = NULL;
	}
	return pStack;
}

Status stack_push(STACK hStack, char item)
{
	Stackptr pStack = (Stackptr)hStack;
	Node* temp;
	temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL)
	{
		return FAILURE;
	}
	temp->data = item;
	temp->next = pStack->head;
	pStack->head = temp;
	return SUCCESS;
}

Status stack_pop(STACK hStack)
{
	Stackptr pStack = (Stackptr)hStack;
	Node* temp;
	if (pStack->head == NULL)
	{
		return FAILURE;
	}
	temp = pStack->head;
	pStack->head = pStack->head->next;
	free(temp);
	return SUCCESS;
}

char stack_top(STACK hStack, Status* pStatus)
{
	Stack* pStack = (Stack*)hStack;
	if (pStatus != NULL)
	{
		*pStatus = SUCCESS;
	}
	return pStack->head->data;
} 


void stack_destroy(STACK* phStack)
{
	Stackptr pStack = (Stackptr)*phStack;
	Node* temp;
		while (pStack->head!=NULL)
		{
			temp = pStack->head;
			pStack->head = pStack->head->next;
			free(temp);
		}
	free(pStack);
	*phStack = NULL;
}

Boolean wordcompare(STACK hStack, char word[])
{
	Stackptr pStack = (Stackptr)hStack;
	if(pStack == NULL)
		return FALSE;
	int j = 0;
	char temp;
	while (word[j] != '\0')
	{
		if(word[j] == '{' || word[j] == '(' || word[j] == '[')
		{
			stack_push(pStack,word[j]);
		}
		else if(word[j] == '}' || word[j] == ')' || word[j] == ']')
		{
			if (pStack->head == NULL)
			{
				return FALSE;
			}
			temp = stack_top(pStack,NULL);
			if (temp == '{' && word[j] == '}')
				stack_pop(pStack);
			else if (temp == '(' && word[j] == ')')
				stack_pop(pStack);
			else if (temp == '[' && word[j] == ']')
				stack_pop(pStack);
			else
				return FALSE;
		}
		
		j++;
	}
	if(!stack_empty(pStack))
		return FALSE;
	else
		return TRUE;
	return TRUE;
}

Boolean stack_empty(STACK hStack)
{
	Stackptr pStack = (Stackptr)hStack;
	if (pStack->head == NULL)
	{
		return TRUE;
	}
	else
		return FALSE;
	return (Boolean)(pStack->head == NULL);
}


void clear_keyboard_buffer(void) 
{
	char ch;
	scanf("%c", &ch);
	while (ch != '\n') 
		scanf("%c", &ch);
	
}