/***********************************************************
Author: Phong Vo
Date: 1/28/2018
Effort: 2 hrs
Purpose: daily 1
***********************************************************/

#include "stdafx.h"
#include "stdio.h"

//function prototype
char* reverse(char word[]);
int main(int argc, char *argv[])
{

	//c -string
	char word[] = "Happy Birthday!";

	printf("%s\n", word);

	//calling reverse
	reverse(word);
	printf("%s\n", word);
	//calling reverse
	printf("%s\n", reverse(word));
	printf("%s\n", word);

}


char* reverse(char word[])
{

	//set i =0
	int i = 0;
	//find the size of the word
	while (word[i] != '\0')
	{
		i++;
	}

	int size = i;
	int j = i - 1;
	i = 0;
	//Reverse the letters of the word
	while (i <= j)
	{
		char temp = word[i];
		word[i] = word[j];
		word[j] = temp;
		i++;
		j--;
	}

	//Terminate with null
	word[size] = '\0';
	//return word
	return word;
}