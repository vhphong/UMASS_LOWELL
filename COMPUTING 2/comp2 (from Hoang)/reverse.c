/*********************************************************** 
Author: Hoang Do
Date: 9/19/2017
Effort: 30 min 
Purpose: Learn how to work with pointer, array
***********************************************************/

#include<stdio.h>

char* reverse(char a[]);

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

char* reverse(char a[])
{
	int length, i;
	for (length = 0; a[length] != '\0'; length++){}
	char temp;
	for (i = 0; i < length / 2; i++){
		temp = a[i];
		a[i] = a[length - i - 1];
		a[length - i - 1] = temp;
	}
	return a;
}
