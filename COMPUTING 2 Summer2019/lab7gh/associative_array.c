#include <stdio.h>
#include <stdlib.h>
#include "my_vector.h"
#include "my_string.h"
#include "associative_array.h"
#include "common.h"

#define max(a,b) ((a)>(b) ? (a) : (b))

GameTree* game_tree_init()
{
    GameTree* temp = (GameTree*)malloc(sizeof(GameTree));

    if (temp != NULL) temp->root = NULL;

    return (GameTree*)temp;
}


void tree_print(Node* tree)
{
    Node* temp_node = (Node*)tree;

    if (temp_node != NULL)
    {
        tree_print(tree->left);
        printf("%5d: %s : %s\n", temp_node->index->get_size(temp_node->index), temp_node->key->c_str(temp_node->key), temp_node->key->c_str(temp_node->index->at(temp_node->index, 0)));

        tree_print(tree->right);
    }
}


MY_VECTOR* get_largest_word_list(GameTree** gt)
{
    Node* temp_node;
   // MY_VECTOR vector;
   // int i;
    int size = 0;
    int *max = &size;

    if ((*gt) == NULL) return NULL;
   
    get_largest_word_list_helper((*gt)->root, &temp_node, max);
    //vector = my_vector_init_default(temp_node->key->item_destroy, temp_node->key->item_assign);

    /*for (i = 0; i < temp_node->index->get_size(temp_node->index); i++)
        vector->push_back(vector, temp_node->index->at(temp_node->index, i));
    return vector;*/

    return &(temp_node->index);
}



void get_largest_word_list_helper(Node* node, Node** temp, int* max)
{
    if (node == NULL) return;

    get_largest_word_list_helper(node->left, temp, max);

    if (node->index->get_size(node->index) > *max)
    {
        *max = node->index->get_size(node->index);
        *temp = node;
    }

    get_largest_word_list_helper(node->right, temp, max);
}


Status tree_insert(GameTree* tree, MY_STRING key, MY_STRING word)
{
    GameTree* gt = (GameTree*)tree;

    if (gt == NULL) return FAILURE;

    return insert(&(gt->root), key, word);
}


Status insert(Node** node, MY_STRING key, MY_STRING word)
{
    Node* temp_node;
    int i = 0;
    int comparison;
    int balance;

    if (*node == NULL)
    {
        temp_node = (Node*)malloc(sizeof(Node));
        if (temp_node == NULL) return FAILURE;

        temp_node->left = NULL;
        temp_node->right = NULL;
        temp_node->height = 1;
        temp_node->key = my_string_init_default();
        temp_node->index = my_vector_init_default(temp_node->key->item_destroy, temp_node->key->item_assign);

        //populate key
        for (i = 0; i < key->get_size(key); i++)
            temp_node->key->push_back(temp_node->key, *key->at(key, i));

        //populate vector
        temp_node->index->push_back(temp_node->index, word);

        *node = temp_node;

        return SUCCESS;
    }

    comparison = key->string_compare(key, (*node)->key);
    if (0 == comparison)
        (*node)->index->push_back((*node)->index, word);
    
    if (-1 == comparison) // -1 means that key is smaller than (*node)->key
        if (insert(&((*node)->left), key, word) == FAILURE) return FAILURE;

    if (1 == comparison)
        if (insert(&((*node)->right), key, word) == FAILURE) return FAILURE;


    (*node)->height = max(height((*node)->left), height((*node)->right)) + 1;

    balance = balance_factor(node);

    if (balance < -1 || balance > 1)
    {
        // Left Heavy Tree
        if (balance < -1 && key->string_compare(key, (*node)->left->key) > 0)
        {
            (*node) = right_rotate(*node);       
            return SUCCESS;
        }

        // Right Heavy Tree
        if (balance > 1 && key->string_compare(key, (*node)->right->key) < 0)
        {
            (*node) = left_rotate(*node);
            return SUCCESS;
        }

        // Left then Right Rotation needed
        if (balance < -1 && key->string_compare(key, (*node)->left->key) > 0)
        {
            //(*node)->left = left_rotate(&(*node)->left);
            (*node)->left = left_rotate((*node)->left);
            (*node) = right_rotate(*node);
            return SUCCESS;
        }

        // Right then Left Rotation needed
        if (balance > 1 && key->string_compare(key, (*node)->right->key) < 0)
        {
            //(*node)->right = right_rotate(&(*node)->right);
            (*node)->right = right_rotate((*node)->right);
            (*node) = left_rotate(*node);
            return SUCCESS;
        }
    }
    
    return SUCCESS;
}


int height(Node* node)
{
    if (node == NULL) return 0;

    return node->height;
}


int balance_factor(Node** node)
{
    if ((*node) == NULL) return 0;
    return height((*node)->right) - height((*node)->left);
}


//TODO: Consider combining Left and Right into one function
Node* left_rotate(Node* node)
{
    Node* node_y = node->right;
    Node* node_y_leaf;

    // Are leaves NULL?
    node_y_leaf = (NULL == node_y->left) ? NULL : node_y->left;

    // Perform rotation
    node_y->left = node;
    node->right = node_y_leaf;

    // Update heights
    node->height = max(height(node->left), height(node->right)) + 1;
    node_y->height = max(height(node_y->left), height(node_y->right)) + 1;


    // Return new root
    return node_y;
}


Node* right_rotate(Node* node)
{
    Node* node_x = node->left;
    Node* node_x_leaf; 

    // Are leaves NULL?
    node_x_leaf = (NULL == node_x->right) ? NULL : node_x->right;

    // Perform rotation
    node_x->right = node;
    node->left = node_x_leaf;


    // Update heights
    node->height = max(height(node_x->left), height(node_x->right)) + 1;
    node_x->height = max(height(node_x->left), height(node_x->right)) + 1;

    // Return new root
    return node_x;
}


void GameTree_destroy(GameTree** phGameTree)
{
    if (phGameTree != NULL)
    {
        GameTree* gt = (GameTree*)*phGameTree;
        if (gt != NULL)
        {
            destroy_helper(gt->root);
            free(gt);
        }
    }
}


void destroy_helper(Node* root)
{
    if (root != NULL)
    {

        if (root->index != NULL)
            root->index->destroy(&root->index);
        

        destroy_helper(root->left);
        destroy_helper(root->right);
        
        root->key->destroy(&root->key);

        free(root);
    }
}

void swap_vectors(MY_VECTOR* destination_vector, MY_VECTOR* source_vector)
{
    MY_VECTOR temp;

    temp = *source_vector;
    *source_vector = *destination_vector;

    *destination_vector = temp;


}