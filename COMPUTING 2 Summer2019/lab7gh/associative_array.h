#ifndef ASSOCIATIVE_ARRAY
#define ASSOCIATIVE_ARAAY

#include "my_string.h"
#include "my_vector.h"


typedef struct node
{
    int height;

    struct node* left;
    struct node* right;

    MY_STRING key;
    MY_VECTOR index;
} Node;

typedef struct gametree
{
    Node* root;
} GameTree;


Node* left_rotate(Node*);
Node* right_rotate(Node*);

Status tree_insert(GameTree*, MY_STRING, MY_STRING);
Status insert(Node**, MY_STRING, MY_STRING);

GameTree* game_tree_init();

//MY_VECTOR get_largest_word_list(GameTree**);

int height(Node*);
int balance_factor(Node**);

void destroy_helper(Node*);
void tree_print(Node* tree);
void print_inorder(Node* tree);
void GameTree_destroy(GameTree**);
void get_largest_word_list_helper(Node*, Node**, int*);
MY_VECTOR* get_largest_word_list(GameTree** gt);
void swap_vectors(MY_VECTOR* destination, MY_VECTOR* source);

#endif