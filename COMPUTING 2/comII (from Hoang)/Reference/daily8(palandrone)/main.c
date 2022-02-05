#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "string.h"
#include "status.h"






int main(int argc, char* argv[])
{
	int i;
	STRING hString = NULL;
	
	hString = string_init_default(1);


	while (get_line(hString, stdin))
	{
		if (is_palindrome(hString))
		{
			printf("Yes\n");
		}
		else
			printf("No\n");
	}


	return 0;
}



