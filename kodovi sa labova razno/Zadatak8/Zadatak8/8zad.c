/* 8. Napisati program koji omogucava rad s binarnim stablom pretrazivanja. Treba
omoguciti unosenje novog elementa u stablo, ispis elemenata (inorder, preorder, postorder i
level order), brisanje i pronalazenje nekog elementa. */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct binarytree;
typedef struct binarytree* Position;
typedef struct binarytree {
    int value;
    Position left;
    Position right;
}BinaryTree;

Position createNode(int value);
Position insert(Position root, int value);
int inorder(Position root);
int preorder(Position root);
int postorder(Position root);
int levelOrder(Position root);
Position deleteNode(Position root, int value);
Position search(Position root, int value);


int main()
{
	Position root = NULL;
    Position result = NULL;
	int choice, value;

    root = insert(root, 5);

	while (1)
	{
		printf("\nChoose an option:\n");
		printf("-----------------------\n");
		printf("1 - create new node\n");
		printf("2 - inorder print\n");
		printf("3 - preorder print\n");
		printf("4 - postorder print\n");
		printf("5 - level order print\n");
		printf("6 - delete node\n");
		printf("7 - find node\n");
		printf("8 - exit\n");
		printf("-----------------------\n");
		scanf_s("%d", &choice);
		printf("\n");

		switch (choice)
		{
		case 1:
			printf("\ncreate new node:\n");
            value = 0;
            printf("enter new node value: ");
            scanf("%d", &value);
            insert(root, value);
			break;

		case 2:
			printf("\ninorder print:\n");
            inorder(root);
			break;

		case 3:
			printf("\npreorder print:\n");
            preorder(root);
			break;

		case 4:
			printf("\npostorder print:\n");
            postorder(root);
			break;

		case 5:
			printf("\nlevel order print:\n");
            levelOrder(root);
			break;

		case 6:
			printf("\ndelete node:\n");
            value = 0;
            printf("enter value to delete: ");
            scanf("%d", &value);
            deleteNode(root, value);
			break;

		case 7:
			printf("\nfind node:\n");
            value = 0;
            printf("enter value to search: ");
            scanf("%d", &value);
            result = search(root, value);
            if (result != NULL)
                printf("\tnode %d was found\n", value);
            else
                printf("\tnode %d was not found\n", value);

			break;

		case 8:
			printf("\nexit\n");
			return 0;
			break;

		default:
			printf("\nError! Enter your choice again:\n");
			break;
		}
	}

    return 0;
}

Position createNode(int value)
{
    Position newNode = NULL;
    newNode = (Position)malloc(sizeof(BinaryTree));

    if (!newNode)
    {
        printf("Can't allocate memory!\n");
        return NULL;
    }

    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Position insert(Position root, int value)
{
    if (root == NULL)
        return createNode(value);

    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value >= root->value)
        root->right = insert(root->right, value);

    return root;
}

int inorder(Position root)
{
    if (root)
    {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }

    printf("\n");

    return EXIT_SUCCESS;
}

int preorder(Position root)
{
    if (root)
    {
        printf("%d ", root->value);
        preorder(root->left);
        preorder(root->right);
    }

    printf("\n");

    return EXIT_SUCCESS;
}

int postorder(Position root)
{
    if (root)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->value);
    }

    printf("\n");

    return EXIT_SUCCESS;
}

int levelOrder(Position root)
{
    if (root == NULL)
        return;

    Position queue[100] = { 0 };
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear)
    {
        Position current = queue[front++];

        printf("%d ", current->value);

        if (current->left != NULL)
            queue[rear++] = current->left;

        if (current->right != NULL)
            queue[rear++] = current->right;
    }

    printf("\n");

    return EXIT_SUCCESS;
}

Position deleteNode(Position root, int value)
{
    if (root == NULL)
        return root;

    if (value < root->value)
        root->left = deleteNode(root->left, value);
    else if (value > root->value)
        root->right = deleteNode(root->right, value);
    else
    {
        if (root->left == NULL)
        {
            Position temp = root->right;
            free(root);
            return temp;
        }

        else if (root->right == NULL)
        {
            Position temp = root->left;
            free(root);
            return temp;
        }

        Position temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;

        root->value = temp->value;

        root->right = deleteNode(root->right, temp->value);
    }

    return root;
}

Position search(Position root, int value)
{
    if (root == NULL || root->value == value)
        return root;

    if (value < root->value)
        return search(root->left, value);

    return search(root->right, value);
}