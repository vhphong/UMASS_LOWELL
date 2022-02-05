

#define BST//--comment this out to switch to AVL Tree implementation

#include "binary_search_tree.h"
struct binarynode {
    String_Ptr key;
    Vector_String_Ptr words;
    unsigned int height;

    struct binarynode *left,*right;
};
typedef struct binarynode BinaryNode, *BinaryNode_Ptr;
struct binarysearchtree {
    BinaryNode_Ptr root;
};
typedef struct binarysearchtree BinarySearchTree,*BinarySearchTree_Ptr;
void binary_search_tree_in_order_traverse_print(BinaryNode_Ptr node);
BinaryNode_Ptr binary_search_tree_recursive_traverse_find_max_size(BinaryNode_Ptr node);

//AVL Tree implementations
int max(int,int);//find the max value between a and b
int avl_tree_get_balance_factor(BinaryNode_Ptr node);//get balance factor of node
BinaryNode_Ptr avl_tree_rotate_left(BinaryNode_Ptr node);
BinaryNode_Ptr avl_tree_rotate_right(BinaryNode_Ptr node);
int avl_tree_get_height(BinaryNode_Ptr node);

// Precondition: none
// Postcondition: returns a handle to a binary search tree
// The function allocates memory for a BinarySearchTree_Ptr
// and sets the root node to null
BinarySearchTree_Ptr binary_search_tree_init_default(){
    BinarySearchTree_Ptr binary_tree_struct = (BinarySearchTree_Ptr)malloc(sizeof(BinarySearchTree));
    if (!binary_tree_struct) {
        return NULL;
    }
    binary_tree_struct->root = NULL;
    return binary_tree_struct;
}

// Precondition: Key is the key to be stored inside the node
// Postcondition: a BinaryNode is created with the given key
// The function copies the given key into the key inside the
// the node. It also calls vector_string_init_default
// to create an empty vector
BinaryNode_Ptr binary_node_init_key(String_Ptr key){
    BinaryNode_Ptr tree_node_struct = (BinaryNode_Ptr)malloc(sizeof(BinaryNode));
    if (!tree_node_struct) {
        free(tree_node_struct);
        tree_node_struct = NULL;
        return NULL;
    }
    tree_node_struct->key = string_init_c_string(string_c_str(key));
    tree_node_struct->words = vector_string_init_default() ;
    tree_node_struct->left = tree_node_struct->right = NULL;
    tree_node_struct->height = 0;
    return tree_node_struct;
}

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
Status binary_search_tree_insert_word(BinarySearchTree_Ptr hTree, String_Ptr word,String_Ptr key){
    BinaryNode_Ptr node_of_key_family = binary_search_tree_search(hTree->root, key);
    if (node_of_key_family) {
        //add matched word of key family to tree
        if (vector_string_push_back(node_of_key_family->words, word) == FAILURE){//push the word into the vector_string array
            return FAILURE;
        }
        //printf("push_back at existing node of family %s\n",string_c_str(node_of_key_family->key));
    }
    else{
        //otherwise, add new node of new key to the tree,recursive call to add word once added new node
        hTree->root = binary_search_tree_insert_node(hTree->root, key);
        binary_search_tree_insert_word(hTree, word, key);
    }
    return SUCCESS;
}
// Precondition: hTree a handle to a tree that would be searched
// key: is the key used in the searching process
// Postcondition: return a pointer to the BinaryNode if found, otherwise,
// return NULL

BinaryNode_Ptr binary_search_tree_search(BinaryNode_Ptr node, String_Ptr key){
    if (!node) {
        //printf("the tree is empty!-tree-search\n");
        return NULL;
    }
    else{
        if (!string_compare(node->key, key)) {
            return node;
        }
        BinaryNode_Ptr tree_node_struct = binary_search_tree_search(node->left, key);
        if (tree_node_struct) {
           // printf("found at left of node %s!\n",string_c_str(node->key));
            return tree_node_struct;
        }
        tree_node_struct = binary_search_tree_search(node->right, key);
        if (tree_node_struct) {
            //printf("found at right of node %s!\n",string_c_str(node->key));
            return tree_node_struct;
        }
        
    }

    //printf("cannot find the node with the key %s!-tree-search\n",string_c_str(key));

    return NULL;
}

// Precondition: hTree is a handle to a tree to add a node to
// Key is the key used to decide where to add a node
// Postcondition: create a new node and add it to the tree based on the key
// Returns a pointer to the new added node
#ifdef BST
BinaryNode_Ptr binary_search_tree_insert_node(BinaryNode_Ptr node, String_Ptr key){
    if (node == NULL) {
        node = ( binary_node_init_key(key));
        return (node);
    }
    
    if (string_compare(node->key, key) > 0) {
            //key < current root, key -->  left
        node->left = binary_search_tree_insert_node(node->left, key);
        node->height++;//increment height since a new node is added
        }
    else if (string_compare(node->key, key) < 0) {
            //key > root key --> right
            node-> right = binary_search_tree_insert_node(node->right, key);
            node->height++;//increment height since a new node is added
        }
    return (node);
}
#endif //BST


//AVL TREE IMPLEMENTATION
#ifndef BST
BinaryNode_Ptr binary_search_tree_insert_node(BinaryNode_Ptr node, String_Ptr key){//changed from the specs
    if (node == NULL) {
        node = binary_node_init_key(key);
        return node;
    }
    
    if (string_compare(node->key, key) > 0) {
        //root > key, key -> left
        node->left = binary_search_tree_insert_node(node->left, key);
    }
    
    else if (string_compare(node->key, key) < 0){
        //root < key, key->right
        node->right = binary_search_tree_insert_node(node->right,key);
    }
    
    //update height: the max value between the height of left node and the height of the right node
    node->height = max(avl_tree_get_height(node->left), avl_tree_get_height(node->right)) + 1;
    
    //find balance factor of node
    int balance = avl_tree_get_balance_factor(node);
    //balance = left-height - right height:
    //if > 1 : tree is unbalanced to the left
    //if < -1 : tree is unbalanced to the right
    //if 1,-1 or 0: tree is balanced
    
    //Left-Left case
    if (balance > 1 && string_compare(node->key, key) > 0) {//tree is unbalanced to the left
        return avl_tree_rotate_right(node);//child node is also unbalanced to the left, rotate right
    }
    
    //Right-Right case
    if (balance < -1 && string_compare(node->key, key) < 0) {//tree is unbalanced to the right
        return avl_tree_rotate_left(node);//child node is also unbalanced to the right, rotate left
    }
    
    //Left-Right case
    if (balance > 1 && string_compare(node->key, key) < 0) {//tree is unbalanced to the left
        node->left = avl_tree_rotate_left(node->left);
        //child node is unbalanced to the right-->make it unbalanced to the left
        return  avl_tree_rotate_right(node);//now we have a left-left case,rotate right
    }
    
    //Right-Left case
    if (balance < -1 && string_compare(node->key, key) > 0) {//tree is unbalanced to the right
        node->right = avl_tree_rotate_right(node->right);
        //child node is unbalanced to the left-->make it unbalanced to the right
        return avl_tree_rotate_left(node);//now we have a right-right case, rotate left
    }
    
    return node;
}
#endif

BinaryNode_Ptr avl_tree_rotate_left(BinaryNode_Ptr node){
    BinaryNode_Ptr right_of_node = node->right;
    BinaryNode_Ptr node_right_left = right_of_node->left;
    
    right_of_node->left = node;
    node->right = node_right_left;
    
    node->height = max(avl_tree_get_height(node->left), avl_tree_get_height(node->right))+1;
    right_of_node->height = max(avl_tree_get_height(right_of_node->left),avl_tree_get_height(right_of_node->left))+1;
    
    return right_of_node;
}

BinaryNode_Ptr avl_tree_rotate_right(BinaryNode_Ptr node){
    BinaryNode_Ptr left_of_node = node->left;
    BinaryNode_Ptr node_left_right = left_of_node->right;
    
    node->left = node_left_right;
    left_of_node->right = node;
    
    
    node->height = max(avl_tree_get_height(node->left), avl_tree_get_height(node->right))+1;
    left_of_node->height = max(avl_tree_get_height(left_of_node->left), avl_tree_get_height(left_of_node->right))+1;
    
    return left_of_node;
}

int avl_tree_get_balance_factor(BinaryNode_Ptr node){//difference between height of left and right
    if (!node) {
        return 0;
    }
    return (avl_tree_get_height(node->left) - avl_tree_get_height(node->right));
}

int max(int a, int b){//find max number between the two
    return (a > b)? a : b;
}

int avl_tree_get_height(BinaryNode_Ptr node){
    if(!node){
        return 0;
    }
    return node->height;
}

// Precondition: hTree is a handle to a binary tree to be searched for
// the given key. hVector is an empty vector.
// Postcondition: returns Success of Failure based on the swapping operation
// The function does the following:
// - It searches for the node that has the given key.
// - Takes an empty string vector (it is allocated in memory but contains no words
//inside)
// - Then it swaps the address of the vector_string inside the found node with the
//given one
// Allowing you to destroy the tree afterwards without any problem
Status binary_search_tree_swap(BinarySearchTree_Ptr hTree, String_Ptr key,Vector_String_Ptr * phVector){
    if (!hTree) {
        //printf("Empty tree-tree_swap\n");
        return FAILURE;
    }
    BinaryNode_Ptr node = binary_search_tree_search(hTree->root, key);
    if (!node) {
        //printf("Can't find the word with the given key-tree-swap\n");
        return FAILURE;
    }
    Vector_String_Ptr pTemp = *phVector;
    *phVector = (node->words);
    node->words = pTemp;//need to do this otherwise,cant destroy tree.
    if (!vector_string_empty(*phVector)) {
        return SUCCESS;
    }
    else{
    //printf("the vector is still empty!-tree-swap\n");
    return FAILURE;
    }
}

// Precondition: hTree is a handle to a binary search tree that would be
// traversed
// Postcondition: returns a pointer to the node with the largest number of
// words
BinaryNode_Ptr binary_search_tree_find_max(BinarySearchTree_Ptr hTree){
    return binary_search_tree_recursive_traverse_find_max_size(hTree->root);
}


BinaryNode_Ptr binary_search_tree_recursive_traverse_find_max_size(BinaryNode_Ptr node){
    
    if (!node) {
        return node;
    }
    //recursively call to traverse->left
    //recursively call to to traverse->right
    
    int left_node_size = 0,right_node_size = 0;
    BinaryNode_Ptr left_node = binary_search_tree_recursive_traverse_find_max_size(node->left);
    BinaryNode_Ptr right_node = binary_search_tree_recursive_traverse_find_max_size(node->right);
    
    int current_node_size = vector_string_get_size(node->words);
    //if right node exist,find size,otherwise, its zero
    if (right_node) {
        right_node_size = vector_string_get_size(right_node->words);
    }
    //if left node exist,find size,otherwise,its zero
    if (left_node) {
        left_node_size = vector_string_get_size(left_node->words);
    }

   // replace max size and node if bigger size detected
    if (current_node_size < left_node_size) {
        current_node_size = left_node_size;
        node = left_node;
    }
    
    if (current_node_size < right_node_size) {
        current_node_size = right_node_size;
        node = right_node;
    }
    
    return node;
}

// Precondition: phTree is a pointer to a handle to a tree that needs to be
// destroyed
// Postcondition: destroys the tree including the nodes
void binary_search_tree_destroy(BinarySearchTree_Ptr * phTree){
    BinarySearchTree_Ptr binary_tree_struct = (BinarySearchTree_Ptr)*phTree;
    if (binary_tree_struct) {
        binary_node_destroy(&binary_tree_struct->root);
        free(binary_tree_struct);
        *phTree = NULL;
    }
}

// Precondition: phNode is a node to destroy
// Postcondition: destroying the node include the key and
// the words vector inside the node
void binary_node_destroy(BinaryNode_Ptr * phNode){
    BinaryNode_Ptr tree_node_struct = (BinaryNode_Ptr)*phNode;
    if (!tree_node_struct) {
        return;
    }
    binary_node_destroy(&(tree_node_struct->left));
    binary_node_destroy(&(tree_node_struct->right));
    string_destroy(&(tree_node_struct->key));
    vector_string_destroy(&(tree_node_struct->words));
    free(tree_node_struct);
    *phNode = NULL;
}

void binary_search_tree_print(BinarySearchTree_Ptr hTree){
    if (!hTree) {
        printf("The tree is empty-tree print!\n");
        return;
    }
    binary_search_tree_in_order_traverse_print(hTree->root);
    return;
}

void binary_search_tree_in_order_traverse_print(BinaryNode_Ptr node){
    if (node == NULL) {
        return;
    }
    else{
        binary_search_tree_in_order_traverse_print(node->left);
        printf("Node key: %s Size: %d\n",string_c_str(node->key),vector_string_get_size(node->words));
        //print_words_inside_node(node);
        binary_search_tree_in_order_traverse_print(node->right);
    }
}

void binary_search_tree_print_words_inside_node(BinaryNode_Ptr node){
    int i;
    for (i = 0; i < vector_string_get_size(node->words); i++) {
        printf("%s at i = %d",string_c_str(*vector_string_at(node->words, i)),i);
        printf("\n");
    }
}

String_Ptr binary_search_tree_get_node_key(BinaryNode_Ptr node){
    return node->key;
}

int binary_search_tree_get_height(BinarySearchTree_Ptr hTree){
    return hTree->root->height;
}

BinaryNode_Ptr binary_search_tree_get_root(BinarySearchTree_Ptr hTree){
    return hTree->root;
}


//load from a vector of strings,filter with key made on the go
BinarySearchTree_Ptr binary_search_tree_load_bst_of_words(Vector_String_Ptr vector_of_words, char guess, String_Ptr old_key){
    BinarySearchTree_Ptr hTree = binary_search_tree_init_default();
    if (vector_string_empty(vector_of_words)) {
        printf("vector string is empty!\n");
        return NULL;
    }
    int i;
    if (hTree) {
        String_Ptr new_key = string_init_default();
        for (i = 0; i < vector_string_get_size(vector_of_words); i++) {
            get_word_key_value(old_key, new_key, *vector_string_at(vector_of_words, i), guess);//load up new key from vector of string
            binary_search_tree_insert_word(hTree, *vector_string_at(vector_of_words, i), new_key);//insert key,if matched key,add word
            //otherwise,create new node of new key then add word
        }
        string_destroy(&new_key);
    }
    return hTree;
    
}
