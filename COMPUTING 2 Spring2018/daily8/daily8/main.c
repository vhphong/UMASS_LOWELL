/***********************************************************
Author: Phong Vo
Date: 04/10/2018
Effort: 10 hrs
Purpose: daily8
Interface proposal: 
***********************************************************/

#include "stdio.h"
#include "priority_queue.h"

int main()
{
	int ch;
	do
	{
		printf("\n[1] Insertion \t[2] Deletion \t[3] Display \t[4] Quit \t: ");
		scanf("%d", &ch);
		switch (ch)
		{
			case 1:
			{
				q_insert();
				break;
			}
			case 2:
			{
				q_del();
				break;
			}
			case 3:
			{
				q_show();
				break;
			}
			default:
			break;
		}
	} while (ch < 4);

}