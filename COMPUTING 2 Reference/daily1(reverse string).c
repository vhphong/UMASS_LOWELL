#include <stdio.h>


/***********************************************
Author: <Rushabh Doshi>
Date: <9-5-2016>
Purpose: <Reverse String in an array using pointers.>
Time Spent: <4-6 hour>
***********************************************/


char * reverse(char * pString)
{
	if (NULL == pString)
		return NULL;
	int size = 0;

	while (pString[size] != '\0')
	{
		size++;
	}
	size--;
	
	char * pStart = pString;
	char * pEnd = pStart + size;
	
	
	while (pEnd > pStart)
	{
		char temp = *pStart;
		*pStart = *pEnd;
		*pEnd = temp;
		
		pStart++;
		pEnd--;
		

	}
	return pString;
}




int main(int argc, char* argv[])
{
	char word[] = "Happy Birthday!";

	printf("%s\n", word);
	reverse(word);
	printf("%s\n", word);
	printf("%s\n", reverse(word));
	printf("%s\n", word);
	

	return 0;
}
