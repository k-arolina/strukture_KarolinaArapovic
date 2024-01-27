/* 9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u cvorove binarnog stabla.
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
sve elemente zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraca
pokazivac na korijen stabla.
b) Napisati funkciju replace koja ce svaki element stabla zamijeniti sumom elemenata u
njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat ce se u stablo na
slici Slika 2.
c) Prepraviti program na nacin da umjesto predefiniranog cjelobrojnog polja koristenjem
funkcije rand() generira slucajne brojeve u rasponu <10, 90>. Takoder, potrebno je
upisati u datoteku sve brojeve u inorder prolasku nakon koristenja funkcije iz a), zatim b)
dijela zadatka. */

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct binarytree;
typedef struct binarytree* Position;
typedef struct binarytree {
	int value;
	Position left;
	Position right;
}BinaryTree;

Position createNode(int value);
Position insertNumber(Position root, int value);
int levelOrder(Position root);
int IspisPreorder(Position root);
int replace(Position root);
int random();

int main()
{
	Position root = NULL;
	Position rootRand = NULL;
	srand(time(0));
	root = insertNumber(root, 2);
	insertNumber(root, 5);
	insertNumber(root, 7);
	insertNumber(root, 8);
	insertNumber(root, 11);
	insertNumber(root, 1);
	insertNumber(root, 4);
	insertNumber(root, 2);
	insertNumber(root, 3);
	insertNumber(root, 7);

	IspisPreorder(root);
	printf("\n");

	levelOrder(root);
	replace(root);

	levelOrder(root);
	printf("\n");
	
	printf("Random brojevi u stablu!\n");
	rootRand = insertNumber(rootRand, random());
	for (int i = 0; i < 10; i++) {
		insertNumber(rootRand, random());
	}
	levelOrder(rootRand);
	return 0;
}
int levelOrder(Position root) {
	if (root == NULL)
		return;

	Position queue[100] = { 0 };
	int front = 0, rear = 0;
	queue[rear++] = root;
	while (front < rear) {
		Position current = queue[front++];
		printf("%d", current->value);

		if (current->left != NULL)
			queue[rear++] = current->left;
		if (current->right != NULL)
			queue[rear++] = current->right;
		printf(" ");
	}
	printf("\n");

	return EXIT_SUCCESS;
}
Position insertNumber(Position root, int value) {


	if (root == NULL) {
		//if tree is  empty
		return createNode(value);
	}

	if (value < root->value) {
		root->left = insertNumber(root->left, value);
	}
	else if (value > root->value) {
		root->right = insertNumber(root->right, value);
	}
	else if (root->value == value) {
		root->right = insertNumber(root->right, value);
	}
	return root;
}
Position createNode(int value) {
	Position newNode = NULL;
	newNode = (Position)malloc(sizeof(BinaryTree));

	if (!newNode) {
		printf("Can't allocate memory!\n");
		return NULL;
	}

	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;



	return newNode;

}
int IspisPreorder(Position root) {
	if (root != NULL) {
		printf("%d ", root->value);
		IspisPreorder(root->left);
		IspisPreorder(root->right);
	}
	return EXIT_SUCCESS;
}
int replace(Position root) {
	if (root == NULL) {
		return 0;
	}
	int leftvalue = replace(root->left);
	int rightvalue = replace(root->right);
	int origValue = root->value;

	root->value = leftvalue + rightvalue;

	return origValue + root->value;
}
int random() {
	return  (rand() % 81) + 10;
}