#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>


struct binarytree;
typedef struct binarytree* Position;
typedef struct binarytree {
	int value;
	Position left;
	Position right;
}BinaryTree;

Position CreateNode(int value);


int main()
{
	Position Root = NULL;
}

Position CreateNode(int value) {
	Position NewNode = NULL;
	NewNode = (Position)malloc(sizeof(BinaryTree));
	NewNode->value = value;
	NewNode->left = NewNode->right = NULL;

	return NewNode;
}

Position Insert()