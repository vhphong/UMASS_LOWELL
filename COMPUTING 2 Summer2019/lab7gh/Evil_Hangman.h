#ifndef EVIL_HANGMAN_H
#define EVIL_HANGMAN_H

#include "my_vector.h"
#include "my_string.h"
#include "common.h"

typedef enum message{ PLAYED = -1, CORRECT, INCORRECT, BLANK } Message;

Boolean remaining_word_count(void);
Boolean has_won(MY_STRING, int);
Boolean alreadyGuessed(MY_STRING, char);

MY_STRING generate_key(MY_STRING, MY_STRING, char, int);

int maxGuess(void);
int wordLength(void);

char playAgain(void);
char evil_hangman(MY_VECTOR*, int, int, Boolean);

void clear_keyboard_buffer(void);
void GuessMessage(Message msg, char guess);

#endif