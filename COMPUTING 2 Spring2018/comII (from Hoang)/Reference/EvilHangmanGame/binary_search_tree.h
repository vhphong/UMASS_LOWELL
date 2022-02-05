

#ifndef binary_search_tree_h
#define binary_search_tree_h
#include "vector_string.h"

typedef struct binarynode *BinaryNode_Ptr;
typedef struct binarysearchtree *BinarySearchTree_Ptr;
// Precondition: none
// Postcondition: returns a handle to a binary search tree
// The function allocates memory for a BinarySearchTree_Ptr
// and sets the root node to null
BinarySearchTree_Ptr binary_search_tree_init_default()
;
// Precondition: Key is the key to be stored inside the node
// Postcondition: a BinaryNode is created with the given key
// The function copies the given key into the key inside the
// the node. It also calls vector_string_init_default
// to create an empty vector
BinaryNode_Ptr binary_node_init_key(String_Ptr key);

// Precondition: hTree is a handle to a binary search tree
// word: is the word to be added to the tree
// key: is the family key to the word. The node will be picked
// based on the key value. The word is inserted in the corresponding
// array in the same node found by the key.
// Postcondition: the word is added to the correct node or a new
// node is created if the key for the word does not exist
// The function does that in two steps:
// - First: call binary_search_tree_search. If the returned node is
// - not null, then the word can be added to the corresponding node
// - Second: if the node returned from the search is null, then call
// - binary_search_tree_insert_node to add a node to the tree with the
// - given key
Status binary_search_tree_insert_word(BinarySearchTree_Ptr hTree, String_Ptr word,String_Ptr key);

// Precondition: hTree a handle to a tree that would be searched
// key: is the key used in the searching process
// Postcondition: return a pointer to the BinaryNode if found, otherwise,
// return NULL
BinaryNode_Ptr binary_search_tree_search(BinaryNode_Ptr node, String_Ptr key);//changed from the specs

// Precondition: hTree is a handle to a tree to add a node to
// Key is the key used to decide where to add a node
// Postcondition: create a new node and add it to the tree based on the key
// Returns a pointer to the new added node
BinaryNode_Ptr binary_search_tree_insert_node(BinaryNode_Ptr node, String_Ptr key);//changed from the specs

// Precondition: hTree is a handle to a binary tree to be searched for
// the given key. hVector is an empty vector.
// Postcondition: returns Success of Failure based on the swapping operation
// The function does the following:
// - It searches for the node that has the given key.
// - Takes an empty string vector (it is allocated in memory but contains no words
//inside)
// - Then it swaps the address of the vector_string inside the found node with the
//given one
// Allowing you to destroy the tree after wards without any problem
Status binary_search_tree_swap(BinarySearchTree_Ptr hTree, String_Ptr key,
                               Vector_String_Ptr * phVector);

// Precondition: hTree is a handle to a binary search tree that would be
// traversed
// Postcondition: returns a pointer to the node with the largest number of
// words
BinaryNode_Ptr binary_search_tree_find_max(BinarySearchTree_Ptr hTree);

// Precondition: phTree is a pointer to a handle to a tree that needs to be
// destroyed
// Postcondition: destroies the tree including the nodes
void binary_search_tree_destroy(BinarySearchTree_Ptr * phTree);

// Precondition: phNode is a node to destroy
// Postcondition: destroying the node include the key and
// the words vector inside the node
void binary_node_destroy(BinaryNode_Ptr * phNode);

//print out tree
void binary_search_tree_print(BinarySearchTree_Ptr hTree);

//print out words inside node
void binary_search_tree_print_words_inside_node(BinaryNode_Ptr node);

//return key from given node
String_Ptr binary_search_tree_get_node_key(BinaryNode_Ptr node);

//return height of tree
int binary_search_tree_get_height(BinarySearchTree_Ptr hTree);
int binary_search_tree_get_node_height(BinaryNode_Ptr node);

//return root of tree
BinaryNode_Ptr binary_search_tree_get_root(BinarySearchTree_Ptr hTree);

//load bst tree of words given vector of words and current key to generate new key
BinarySearchTree_Ptr binary_search_tree_load_bst_of_words(Vector_String_Ptr vector_of_words, char guess, String_Ptr old_key);
#endif /* binary_search_tree_h */
