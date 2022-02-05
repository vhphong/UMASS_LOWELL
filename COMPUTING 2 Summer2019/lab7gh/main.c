#define _CRT_SECURE_NO_WARNINGS
#define MAX_WORD_LEN 29

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "my_vector.h"
#include "Evil_Hangman.h"

#if defined POSIX || defined __linux__
#define CLEARSCREEN system ( "clear" )
#elif defined MSDOS || defined WIN32
#define CLEARSCREEN system ( "cls" )
#endif


int main(int argc, const char * argv[])
{
    FILE* dictionary;
    Boolean show_word_count;
    MY_VECTOR arr[MAX_WORD_LEN];
    MY_STRING hString = my_string_init_default();

    int i = 0;
    int size = -1;
    int wordLen;
    int guessCount;

    char playAgain;

    for (i = 0; i<MAX_WORD_LEN; i++)
        arr[i] = my_vector_init_default(hString->item_destroy, hString->item_assign);

    dictionary = fopen("dictionary.txt", "r");

    while (hString->extraction(hString, dictionary) == SUCCESS)
    {
        size = hString->get_size(hString) - 1;

        if (size < 0) break;

        arr[size]->push_back(arr[size], hString);

    }

    fclose(dictionary);

    CLEARSCREEN;

    do
    {
        srand((unsigned) time(NULL));
        printf("-= Evil Hangman =-\n");
        printf("What word length would you like to play with: ");

        wordLen = wordLength();
        if (wordLen == 0) break;  // provides quick/silent exit.  it's an undocumented feature!

        guessCount = maxGuess();
        show_word_count = remaining_word_count();
        
        playAgain = evil_hangman(arr, wordLen, guessCount, show_word_count);

    } while (playAgain == 'y' || playAgain == 'Y');

    for (i = 0; i < MAX_WORD_LEN; i++)
        arr[i]->destroy(&arr[i]);

    hString->destroy(&hString);
    return 0;
}