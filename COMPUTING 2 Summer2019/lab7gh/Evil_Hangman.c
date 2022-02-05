#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_vector.h"
#include "my_string.h"
#include "associative_array.h"
#include "common.h"
#include "Evil_Hangman.h"

#if defined POSIX || defined __linux__
#define CLEARSCREEN system ( "clear" )
#elif defined MSDOS || defined WIN32
#define CLEARSCREEN system ( "cls" )
#endif

char evil_hangman(MY_VECTOR* dictionary, int word_length, int guesses_remaining, Boolean show_word_count)
{
    MY_STRING chosenLetters = my_string_init_default();
    MY_STRING guess_current = my_string_init_default();
    MY_STRING key_initial = my_string_init_default();

    MY_STRING word_current;
    MY_STRING key_generated;
    MY_STRING key_current;

    MY_VECTOR wordListVector = my_vector_init_default(guess_current->item_destroy, guess_current->item_assign);

    GameTree* word_groups;

    Status insertStatus;
    Message msg = BLANK;

    Boolean check_win;

    int i;
    int random;
    int word_list_size;
    int correctGuessCount = 0;
    int conversion;

    char guess = ' ';

    for (i = 0; i<word_length; i++)
        key_initial->push_back(key_initial, '-');

    for (i = 0; i < (*dictionary)->get_size(dictionary[word_length - 1]); i++)
        wordListVector->push_back(wordListVector, dictionary[word_length - 1]->at(dictionary[word_length - 1], i));


    while (guesses_remaining > 0)
    {
        CLEARSCREEN; 
        word_list_size = wordListVector->get_size(wordListVector);
        if (show_word_count == TRUE) printf("Words remaining: %d\n\n", word_list_size);

        printf("Guesses Remaining: %d\n", guesses_remaining);
        printf("Letters Chosen So Far: %s\n", chosenLetters->c_str(chosenLetters));
        printf("Word: %s\n", key_initial->c_str(key_initial));
        GuessMessage(msg, guess);

        printf("\nEnter your guess: ");
        conversion = fscanf(stdin, "%c", &guess);

        msg = BLANK;
        clear_keyboard_buffer();

        while (conversion < 1 || !isalpha(guess))
        {
            printf("Error:  Invalid input\n");
            printf("Enter your guess: ");
            conversion = fscanf(stdin, "%c", &guess);
            clear_keyboard_buffer();
        }

        printf("\n");
        guess = tolower(guess);

        if (!(alreadyGuessed(chosenLetters, guess)))
        {
            chosenLetters->push_back(chosenLetters, guess);
            chosenLetters->push_back(chosenLetters, ' ');
        }
        else
            correctGuessCount = -1;

        GuessMessage(msg, guess);
        
        //create new tree to populate with based off guesses
        word_groups = game_tree_init();

        //generate keys based off remaining words in list
        for (i = 0; i<word_list_size; i++)
        {
            word_current = wordListVector->at(wordListVector, i);  //select a word
            key_generated = generate_key(word_current, key_initial, guess, word_length);  //build a key based off of it, the players guess, and the current state of the key
            insertStatus = tree_insert(word_groups, key_generated, word_current);  //placee the key and the word into the game tree

            if (insertStatus == FAILURE)
            {
                printf("Failed to insert word into GameTree.  Exiting...\n");
                exit(1);
            }
            
            key_generated->destroy(&key_generated); 
        }
        
        //tree_print(word_groups->root);  //debug statement
        //printf("height: %d\n", word_groups->root->height); //debug statement

        wordListVector->destroy(&wordListVector);  //destroy current word list
        swap_vectors(&wordListVector, get_largest_word_list(&word_groups));  //swap the largest vector instead of deep copying to increase performance
        

        random = rand() % wordListVector->get_size(wordListVector); 
        word_current = wordListVector->at(wordListVector, random);  // select a random word from the new list
        key_current = generate_key(word_current, key_initial, guess, word_length);  //generate a key based off the new word list

        key_initial->destroy(&key_initial);  // delete the previous key
        key_initial = my_string_init_default();

        for (i = 0; i < word_length; i++)
            key_initial->push_back(key_initial, *key_current->at(key_current, i));
        
        key_current->destroy(&key_current);

        GameTree_destroy(&word_groups); // destroy the game tree

        for (i = 0; i < word_length; i++)
            if (*key_initial->at(key_initial, i) == guess) correctGuessCount++;

        if (correctGuessCount > 0) msg = CORRECT;
        else if (correctGuessCount < 0) msg = PLAYED;        
        else
        {
            msg = INCORRECT;
            guesses_remaining--;
        }

        correctGuessCount = 0;

        check_win = has_won(key_initial, word_length);

        if (check_win == TRUE)
        {
            printf("Congratulations!\n");
            printf("The word was: %s\n\n", word_current->c_str(word_current));
            break;
        }
        else if (guesses_remaining <= 0)
        {
            random = rand() % wordListVector->get_size(wordListVector);
            printf("YOU LOSE! GOOD DAY, SIR!\n");
            printf("The word was: %s\n\n", word_current->c_str(wordListVector->at(wordListVector, random)));
        }
    }

    // cleanup after game ends
    key_initial->destroy(&key_initial);
    guess_current->destroy(&guess_current);
    chosenLetters->destroy(&chosenLetters);
    wordListVector->destroy(&wordListVector);

    return playAgain();
}

void GuessMessage(Message msg, char guess)
{
    switch (msg)
    {
    case PLAYED:
        printf("\nLetter '%c' has already been played.  Choose again.\n", guess);
        break;
    case CORRECT:
        printf("\nLucky guess! There's a \'%c\' in the word!\n", guess);
        break;
    case INCORRECT:
        printf("\nThis is why you can't have nice things.\nThe letter \'%c\' is not in the selected word!\n", guess);
        break;
    case BLANK:
        // display nothing
        break;
    }
}

Boolean alreadyGuessed(MY_STRING previous_guesses, char guess)
{
    int i;

    for (i = 0; i<previous_guesses->get_size(previous_guesses); i++)
        if ( *(previous_guesses->at(previous_guesses, i)) == guess) return TRUE;

    return FALSE;
}


int wordLength(void)
{
    // TODO: Calculate word lengths instead of hard coding -- otherwise change output message...
    int word_length;

    fscanf(stdin, "%d", &word_length);
    clear_keyboard_buffer();

    if (word_length == 0) return word_length; // allow for quick exit

    while (word_length < 2 || word_length >29 || word_length == 27 || word_length == 26 || word_length == 23 || word_length == 25)
    {
        printf("Invalid word length.  Choose again: ");
        fscanf(stdin, "%d", &word_length);
        clear_keyboard_buffer();
    }

    return word_length;
}


int maxGuess(void)
{
    int number_of_guesses;
    int conversion;

    printf("How many guesses would you like: ");
    conversion = fscanf(stdin, "%d", &number_of_guesses);
    clear_keyboard_buffer();

    while (number_of_guesses <0)
    {
        if (conversion < 1) printf("Invalid input.\n");
        if (conversion >= 1) printf("%d is too low.  Choose a less ludicrous number...\n", number_of_guesses);
        printf("How many guesses would you like: ");
        fscanf(stdin, "%d", &number_of_guesses);
        clear_keyboard_buffer();
    }

    return number_of_guesses;
}


Boolean remaining_word_count(void)
{
    char countWords;

    printf("Would you like to see a count of how many words remain after each turn (y/n): ");
    fscanf(stdin, "%c", &countWords);
    clear_keyboard_buffer();

    while (countWords != 'y' && countWords != 'Y' && countWords != 'n' && countWords != 'N')
    {
        printf("\n\nError: invalid input\n");
        printf("Would you like to see a count of how many words remain after each turn (y/n): ");
        fscanf(stdin, "%c", &countWords);
        clear_keyboard_buffer();
    }

    return (countWords == 'y' || countWords == 'Y') ? TRUE : FALSE;
}


Boolean has_won(MY_STRING key, int word_size)
{
    int i = 0;
    int remainingLetters = 0;

    for (i = 0; i<word_size; i++)
        if (*(key->at(key, i)) == '-') remainingLetters++;

    return (remainingLetters == 0) ? TRUE : FALSE;
}


MY_STRING generate_key(MY_STRING current_word, MY_STRING current_key, char guess, int word_length)
{
    int i;
    MY_STRING key = my_string_init_default();

    for (i = 0; i < word_length; i++)
    {
        if (*(current_word->at(current_word, i)) == guess)
            key->push_back(key, guess);
        else
            key->push_back(key, *(current_key->at(current_key, i)));
    }

    return key;
}


char playAgain(void)
{
    char choice;

    printf("Would you like to play again (y/n): ");
    fscanf(stdin, " %c", &choice);

    while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
    {
        printf("Would you like to play again (y/n): ");
        fscanf(stdin, " %c", &choice);
    }

    CLEARSCREEN;

    return tolower(choice);
}


void clear_keyboard_buffer(void)
{
    char c;

    do
    {
        scanf("%c", &c);
    } while (c != '\n');
}