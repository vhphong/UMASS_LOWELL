

#ifndef binary_search_tree_h
#define binary_search_tree_h
#include "vector_string.h"

typedef struct binarynode *BinaryNode_Ptr;
typedef struct binarysearchtree *BinarySearchTree_Ptr;

BinarySearchTree_Ptr binary_search_tree_init_default();

BinaryNode_Ptr binary_node_init_key(MY_STRING key);

Status binary_search_tree_insert_word(BinarySearchTree_Ptr hTree, MY_STRING word,MY_STRING key);

BinaryNode_Ptr binary_search_tree_search(BinaryNode_Ptr node, MY_STRING key);

BinaryNode_Ptr binary_search_tree_insert_node(BinaryNode_Ptr node, MY_STRING key);

Status binary_search_tree_swap(BinarySearchTree_Ptr hTree, MY_STRING key,
                               Vector_String_Ptr * phVector);


BinaryNode_Ptr binary_search_tree_find_max(BinarySearchTree_Ptr hTree);


void binary_search_tree_destroy(BinarySearchTree_Ptr * phTree);

void binary_node_destroy(BinaryNode_Ptr * phNode);

void binary_search_tree_print(BinarySearchTree_Ptr hTree);

void binary_search_tree_print_words_inside_node(BinaryNode_Ptr node);

MY_STRING binary_search_tree_get_node_key(BinaryNode_Ptr node);

int binary_search_tree_get_height(BinarySearchTree_Ptr hTree);
int binary_search_tree_get_node_height(BinaryNode_Ptr node);

BinaryNode_Ptr binary_search_tree_get_root(BinarySearchTree_Ptr hTree);

BinarySearchTree_Ptr binary_search_tree_load_bst_of_words(Vector_String_Ptr vector_of_words, char guess, MY_STRING old_key);
#endif 
