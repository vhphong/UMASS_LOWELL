/***********************************************************
Author: Phong Vo
Date: 02/23/2018
Effort: 10 hrs
Purpose: daily7
Interface proposal: 
***********************************************************/

struct sNode
{
	char data;
	struct sNode *next;
};
typedef struct sNode Node, *pNode;

enum status { FAILURE, SUCCESS };
typedef enum status Status;

enum boolean { FALSE, TRUE };
typedef enum boolean Boolean;

Status stack_push(pNode* head, char item);
char stack_pop(pNode* head);
Boolean parenthesisBalanced(char ch[]);
Boolean isMatchingPair(char c1, char c2);
void clear_keyboard_buffer(void);