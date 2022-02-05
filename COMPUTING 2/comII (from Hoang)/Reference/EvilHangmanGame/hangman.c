

#include "binary_search_tree.h"

int get_word_length(void);
int get_no_of_guesses(void);
Boolean display_answer_or_not(void);
char get_char_input(String_Ptr user_guesses);
char evil_hangman(int len,int no_of_guesses,Boolean reveal);

int main(int argc, const char * argv[]) {
    char keep_playing = 'y';
    int len;
    int no_of_guesses;
    Boolean reveal = FALSE;
    
    while (tolower(keep_playing) == 'y') {
        //Obtain word length
        len = get_word_length();
        
        //Obtain number of times user wants to try guessing the word
        no_of_guesses = get_no_of_guesses();
        
        //If user want to display word and number of words left
        reveal = display_answer_or_not();
        
        keep_playing = evil_hangman(len, no_of_guesses, reveal);
    }
    
    fclose(stdin);


    return 0;
}


int get_word_length(void) {
    int len = 0;
    Vector_String_Ptr word_pool;
    while (len < 2|| len > 29) {
        printf("The longest word is 29 characters long and \nthe shortest one is 2 characters long.\n");
        printf("Enter a number for the word length: ");
        scanf("%d",&len);
    }
    
    word_pool = vector_string_init_default();
    //load up vector of string of given size,only load one word
    vector_string_load_one_word_of_size(len, word_pool);

    //dynamically find gaps within provided dictionary txt file
    //once loaded up vector of string of given size
    //--> need to check if there is any word at given length
    //->if empty,keep asking for a diff length
    //invalid length of current dictionary file at the time of writing is 23,25,26,27,<2, and >29
    while (vector_string_empty(word_pool)) {
        printf("The current dictionary does not support words at this length.\n");
        printf("Enter another number(between 2 and 29)for the word length: ");
        scanf("%d",&len);
        if (len < 2 || len > 29) {//=_____=
            continue;
        }
        vector_string_load_one_word_of_size(len, word_pool);//reload with new length and check again
    }

    vector_string_destroy(&word_pool);
    
    return len;
}

int get_no_of_guesses(void){
    int no_of_guesses = 0;
    while (no_of_guesses < 1) {
        printf("Enter a positive number for the number of guesses you need: ");
        scanf("%d",&no_of_guesses);//o_o
    }
    return no_of_guesses;
}

Boolean display_answer_or_not(void){
    Boolean reveal = FALSE;
    char reveal_input;
    printf("Do you want the answer displayed while playing the game?\nEnter y(yes) or n(no): ");
    scanf(" %c",&reveal_input);
    if (tolower(reveal_input) == 'y') {
        reveal = TRUE;
    }
    return reveal;
}

char get_char_input(String_Ptr user_guesses){
    char c;
    int i;
    do{
        printf("\nPlease enter a letter from the English alphabet: ");//@_@
        scanf(" %c",&c);
    }while (!isalpha(c));
    c = tolower(c);
    
    //check for duplicates in user input
    for (i = 0 ; i <string_get_size(user_guesses); i++) {
        while ((c) == string_c_str(user_guesses)[i]) {
            printf("You already have entered '%c' before.\nThe letter(s) you have entered so far: ",c);
            string_print(user_guesses);
            printf("Please enter a different letter from those: ");
            scanf(" %c",&c);
            while(!isalpha(c)){
                printf("Please enter a letter from the English alphabet: ");//o_o O(n2)
                scanf(" %c",&c);
                
            }
            c = tolower(c);
            i = 0;
        }
    }
    string_push_back(user_guesses, c);
    return c;
}

char evil_hangman(int len,int no_of_guesses,Boolean reveal){
    
    BinarySearchTree_Ptr hTree = NULL;
    BinaryNode_Ptr biggest_node = NULL;
    char keep_playing;
    char c;
    int i;
    String_Ptr current_word_family = string_init_default();
    String_Ptr user_guesses = string_init_default();
    
    Vector_String_Ptr dictionary = load_dictionary_of_size(len);
    
    for (i = 0; i < len; i++) {
        string_push_back(current_word_family, '-');//default key
    }
    
    while (no_of_guesses--) {
        
        c = get_char_input(user_guesses);
        //narrow down the tree as players enter guesses together with the key of that word pool
        
        hTree = binary_search_tree_load_bst_of_words(dictionary, c, current_word_family);//load from previous word pool
        //binary_search_tree_print(hTree);//print entire tree of key
        
        if (binary_search_tree_get_height(hTree)>0){
            //find biggest node if height > 0
            biggest_node = binary_search_tree_find_max(hTree);
        }
        else biggest_node = binary_search_tree_get_root(hTree);//when height  = 0, root is the only node
        printf("Word: %s\n",string_c_str(binary_search_tree_get_node_key(biggest_node)));
        
        string_destroy(&current_word_family);//update word_family or current key of the biggest node
        current_word_family = string_init_c_string(string_c_str(binary_search_tree_get_node_key(biggest_node)));
        
       //let user know if they got any char right
        string_print_matched_char(current_word_family, c);
        
        vector_string_destroy(&dictionary);
        dictionary = vector_string_init_default();//swap out the word pool using vector_string with the biggest node
        binary_search_tree_swap(hTree, (binary_search_tree_get_node_key(biggest_node)), &dictionary);
        
        if (reveal) {
            printf("I have %d word(s) left\n",vector_string_get_size(dictionary));
            printf("The word I'm thinking about is %s\n",string_c_str(*vector_string_at(dictionary, 0)));
        }
        
        printf("You entered: ");
        string_print(user_guesses);//print out all of user guesses
        
        //all char are correctly guessed = win
        if (!string_compare(*vector_string_at(dictionary, 0), current_word_family)) {
            printf("Congratulation! You won!!!!!\n");
            no_of_guesses = 0;
        }
        
        //keep going if still have attempts left
        if (no_of_guesses) {
            printf("You have %d attempts left\n",no_of_guesses);
        }
        
        //used up all guesses and word is still incomplete = lost
        if (!no_of_guesses && string_compare(*vector_string_at(dictionary, 0), current_word_family)) {
            printf("You lost!\n");
            no_of_guesses = 0;
        }
        
        binary_search_tree_destroy(&hTree);
    }
    
    if (!reveal) {
        printf("The word I'm thinking about is %s\n",string_c_str(*vector_string_at(dictionary, 0)));
    }
    
    vector_string_destroy(&dictionary);
    string_destroy(&current_word_family);
    string_destroy(&user_guesses);
    printf("\nDo you want to continue? Enter y(yes) or n(no)");
    scanf(" %c",&keep_playing);
    printf("\n");

    return keep_playing;
}
