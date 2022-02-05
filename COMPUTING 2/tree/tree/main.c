#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	// int count;
	Node* left, right;
};

void tree_insert(Node** pRoot, int item);
void tree_destroy(Node** pRoot);
void preorder_traversal(Node* root);
void postorder_traversal(Node* root);
void inorder_traversal(Node* root);

int main(int argc, char* argv[])
{
	Node* root = NULL;
	tree_insert(root, 5);
	tree_insert(root, 8);
	tree_insert(root, 7);
	tree_insert(root, 90);
	tree_insert(root, 12);
	tree_insert(root, 10);
	tree_insert(root, 100);
	tree_insert(root, 75);
	tree_destroy(&root);
	getchar();

	return 0;
}

void tree_insert(Node** pRoot, int item)
{
	if (*pRoot == NULL)
	{
		*pRoot = (Node*)malloc(sizeof(Node));
		if (*pRoot == NULL) {
			printf("Failed\n");
			exit(1);
		}
		(*pRoot)->data = item;
		(*pRoot)->left = NULL;
		(*pRoot)->right = NULL;
	}
	else
	{
		if (item < (*pRoot)->data)
		{
			tree_insert(&(*pRoot)->left, item);
		}
		else
		{
			tree_insert(&(*pRoot)->right, item);
		}
	}
}

void tree_destroy(Node** pRoot)
{
	if (*pRoot != NULL)
	{
		tree_destroy(&(*pRoot)->left);
		tree_destroy(&(*pRoot)->right);
		free(*pRoot);
		*pRoot = NULL;
	}
}

void preorder_traversal(Node* root)
{
	if (root != NULL)
	{
		printf("%d\n", root->data);
		preorder_traversal(root->left);
		preorder_traversal(root->right);
	}
}
void postorder_traversal(Node* root)
{

}
void inorder_traversal(Node* root)
{

}