#define BST//--switch to AVL Tree implementation

#include "binary_search_tree.h"
struct binarynode {
    MY_STRING key;
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
int max(int,int);
int avl_tree_get_balance_factor(BinaryNode_Ptr node);
BinaryNode_Ptr avl_tree_rotate_left(BinaryNode_Ptr node);
BinaryNode_Ptr avl_tree_rotate_right(BinaryNode_Ptr node);
int avl_tree_get_height(BinaryNode_Ptr node);

BinarySearchTree_Ptr binary_search_tree_init_default(){
    BinarySearchTree_Ptr binary_tree_struct = (BinarySearchTree_Ptr)malloc(sizeof(BinarySearchTree));
    if (!binary_tree_struct) {
        return NULL;
    }
    binary_tree_struct->root = NULL;
    return binary_tree_struct;
}

BinaryNode_Ptr binary_node_init_key(MY_STRING key){
    BinaryNode_Ptr tree_node_struct = (BinaryNode_Ptr)malloc(sizeof(BinaryNode));
    if (!tree_node_struct) {
        free(tree_node_struct);
        tree_node_struct = NULL;
        return NULL;
    }
    tree_node_struct->key = my_string_init_c_string(my_string_c_str(key));
    tree_node_struct->words = vector_string_init_default() ;
    tree_node_struct->left = tree_node_struct->right = NULL;
    tree_node_struct->height = 0;
    return tree_node_struct;
}

Status binary_search_tree_insert_word(BinarySearchTree_Ptr hTree, MY_STRING word,MY_STRING key){
    BinaryNode_Ptr node_of_key_family = binary_search_tree_search(hTree->root, key);
    if (node_of_key_family) {
        if (vector_string_push_back(node_of_key_family->words, word) == FAILURE){
            return FAILURE;
        }
    }
    else{
        hTree->root = binary_search_tree_insert_node(hTree->root, key);
        binary_search_tree_insert_word(hTree, word, key);
    }
    return SUCCESS;
}

BinaryNode_Ptr binary_search_tree_search(BinaryNode_Ptr node, MY_STRING key){
    if (!node) {
        return NULL;
    }
    else{
        if (!my_string_compare(node->key, key)) {
            return node;
        }
        BinaryNode_Ptr tree_node_struct = binary_search_tree_search(node->left, key);
        if (tree_node_struct) {
            return tree_node_struct;
        }
        tree_node_struct = binary_search_tree_search(node->right, key);
        if (tree_node_struct) {
            return tree_node_struct;
        }
        
    }
    return NULL;
}

#ifdef BST
BinaryNode_Ptr binary_search_tree_insert_node(BinaryNode_Ptr node, MY_STRING key){
    if (node == NULL) {
        node = ( binary_node_init_key(key));
        return (node);
    }
    
    if (my_string_compare(node->key, key) > 0) {
        node->left = binary_search_tree_insert_node(node->left, key);
        node->height++;
        }
    else if (my_string_compare(node->key, key) < 0) {
            node-> right = binary_search_tree_insert_node(node->right, key);
            node->height++;
        }
    return (node);
}
#endif //BST


//AVL TREE IMPLEMENTATION
#ifndef BST
BinaryNode_Ptr binary_search_tree_insert_node(BinaryNode_Ptr node, MY_STRING key){
    if (node == NULL) {
        node = binary_node_init_key(key);
        return node;
    }
    
    if (my_string_compare(node->key, key) > 0) {
        node->left = binary_search_tree_insert_node(node->left, key);
    }
    
    else if (my_string_compare(node->key, key) < 0){
        node->right = binary_search_tree_insert_node(node->right,key);
    }
    
    
    node->height = max(avl_tree_get_height(node->left), avl_tree_get_height(node->right)) + 1;

    int balance = avl_tree_get_balance_factor(node);
    //balance = left-height - right height:
    
    //Left-Left 
    if (balance > 1 && my_string_compare(node->key, key) > 0) {
        return avl_tree_rotate_right(node);
    }
    
    //Right-Right 
    if (balance < -1 && my_string_compare(node->key, key) < 0) {
        return avl_tree_rotate_left(node);
    }
    
    //Left-Right 
    if (balance > 1 && my_string_compare(node->key, key) < 0) {
        node->left = avl_tree_rotate_left(node->left);
        return  avl_tree_rotate_right(node);
    }
    
    //Right-Left 
    if (balance < -1 && my_string_compare(node->key, key) > 0) {
        node->right = avl_tree_rotate_right(node->right);
        return avl_tree_rotate_left(node);
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

int avl_tree_get_balance_factor(BinaryNode_Ptr node){
    if (!node) {
        return 0;
    }
    return (avl_tree_get_height(node->left) - avl_tree_get_height(node->right));
}

int max(int a, int b){
    return (a > b)? a : b;
}

int avl_tree_get_height(BinaryNode_Ptr node){
    if(!node){
        return 0;
    }
    return node->height;
}

Status binary_search_tree_swap(BinarySearchTree_Ptr hTree, MY_STRING key,Vector_String_Ptr * phVector){
    if (!hTree) {
        return FAILURE;
    }
    BinaryNode_Ptr node = binary_search_tree_search(hTree->root, key);
    if (!node) {
        return FAILURE;
    }
    Vector_String_Ptr pTemp = *phVector;
    *phVector = (node->words);
    node->words = pTemp;
    if (!vector_string_empty(*phVector)) {
        return SUCCESS;
    }
    else{
    return FAILURE;
    }
}

BinaryNode_Ptr binary_search_tree_find_max(BinarySearchTree_Ptr hTree){
    return binary_search_tree_recursive_traverse_find_max_size(hTree->root);
}


BinaryNode_Ptr binary_search_tree_recursive_traverse_find_max_size(BinaryNode_Ptr node){
    
    if (!node) {
        return node;
    }
    
    int left_node_size = 0,right_node_size = 0;
    BinaryNode_Ptr left_node = binary_search_tree_recursive_traverse_find_max_size(node->left);
    BinaryNode_Ptr right_node = binary_search_tree_recursive_traverse_find_max_size(node->right);
    
    int current_node_size = vector_string_get_size(node->words);
    if (right_node) {
        right_node_size = vector_string_get_size(right_node->words);
    }
    if (left_node) {
        left_node_size = vector_string_get_size(left_node->words);
    }

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

void binary_search_tree_destroy(BinarySearchTree_Ptr * phTree){
    BinarySearchTree_Ptr binary_tree_struct = (BinarySearchTree_Ptr)*phTree;
    if (binary_tree_struct) {
        binary_node_destroy(&binary_tree_struct->root);
        free(binary_tree_struct);
        *phTree = NULL;
    }
}

void binary_node_destroy(BinaryNode_Ptr * phNode){
    BinaryNode_Ptr tree_node_struct = (BinaryNode_Ptr)*phNode;
    if (!tree_node_struct) {
        return;
    }
    binary_node_destroy(&(tree_node_struct->left));
    binary_node_destroy(&(tree_node_struct->right));
    my_string_destroy(&(tree_node_struct->key));
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
        printf("Node key: %s Size: %d\n",my_string_c_str(node->key),vector_string_get_size(node->words));
        binary_search_tree_in_order_traverse_print(node->right);
    }
}

void binary_search_tree_print_words_inside_node(BinaryNode_Ptr node){
    int i;
    for (i = 0; i < vector_string_get_size(node->words); i++) {
        printf("%s at i = %d",my_string_c_str(*vector_string_at(node->words, i)),i);
        printf("\n");
    }
}

MY_STRING binary_search_tree_get_node_key(BinaryNode_Ptr node){
    return node->key;
}

int binary_search_tree_get_height(BinarySearchTree_Ptr hTree){
    return hTree->root->height;
}

BinaryNode_Ptr binary_search_tree_get_root(BinarySearchTree_Ptr hTree){
    return hTree->root;
}

BinarySearchTree_Ptr binary_search_tree_load_bst_of_words(Vector_String_Ptr vector_of_words, char guess, MY_STRING old_key){
    BinarySearchTree_Ptr hTree = binary_search_tree_init_default();
    if (vector_string_empty(vector_of_words)) {
        printf("vector string is empty!\n");
        return NULL;
    }
    int i;
    if (hTree) {
        MY_STRING new_key = my_string_init_default();
        for (i = 0; i < vector_string_get_size(vector_of_words); i++) {
            get_word_key_value(old_key, new_key, *vector_string_at(vector_of_words, i), guess);
            binary_search_tree_insert_word(hTree, *vector_string_at(vector_of_words, i), new_key);
        }
        my_string_destroy(&new_key);
    }
    return hTree;
    
}
