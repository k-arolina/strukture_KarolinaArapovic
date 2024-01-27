/* 4. Napisati program za zbrajanje i mnozenje polinoma. Koeficijenti i eksponenti se
citaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nuzno sortirani. */


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1024
#define FILE_NOT_OPEN -1
#define LIST_EMPTY -2
#define MEM_ALLOC_FAIL NULL

struct _Polynome;
typedef struct _Polynome* Position;
typedef struct _Polynome {
	int Coefficient;
	int Exponent;
	Position Next;
} Polynome;

int readPoly(Position P1, Position P2);
int readFileIntoList(Position P, char* buffer);
Position createElement(int coef, int exp);
int insertSorted(Position P, Position newPolynome);
int mergeElements(Position current, Position newPolynome);
int printPoly(char* polynomeName, Position first);
int connectList(Position P, Position newPolynome);
int polySum(Position PolySum, Position Poly1, Position Poly2);
int sortedInput(Position headPoly, Position newElement);
int insertNewElement(int coef, int exp, Position current);
int polyProduct(Position Poly1, Position Poly2, Position headPolyProduct);
int freeMemory(Position P);
int deleteAfter(Position previous);

int main()
{
	Polynome headPoly1 = { .Coefficient = 0, .Exponent = 0, .Next = NULL };
	Polynome headPoly2 = { .Coefficient = 0, .Exponent = 0, .Next = NULL };
	Polynome headPolySum = { .Coefficient = 0, .Exponent = 0, .Next = NULL };
	Polynome headPolyMultiply = { .Coefficient = 0, .Exponent = 0, .Next = NULL };


	if (readPoly(&headPoly1, &headPoly2) == EXIT_SUCCESS)
	{
		printf("File read successfully!\n\n");
		printPoly("First polynome: ", headPoly1.Next);
		printPoly("Second polynome: ", headPoly2.Next);

		polySum(headPoly1.Next, headPoly2.Next, &headPolySum);
		printPoly("Polynome sum: ", headPolySum.Next);

		polyProduct(&headPolyMultiply, headPoly1.Next, headPoly2.Next);
		printPoly("Polynome product: ", headPolyMultiply.Next);

		freeMemory(&headPoly1);
		freeMemory(&headPoly2);
		freeMemory(&headPolySum);
		freeMemory(&headPolyMultiply);
	}

	return 0;
}

int readPoly(Position P1, Position P2)
{
	FILE* filePointer = NULL;
	char buffer[MAX_LENGTH] = { 0 };
	int status = EXIT_SUCCESS;

	filePointer = fopen("polynome.txt", "r");
	if (!filePointer) {
		printf("File open unsuccessful\n");
		return FILE_NOT_OPEN;
	}

	fgets(buffer, MAX_LENGTH, filePointer);		// procita prvu liniju datoteke i spremi je u buffer
	// to nam je prvi polinom

	status = readFileIntoList(P1, buffer);
	if (status != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LENGTH, filePointer);		// procita drugu liniju datoteke, to je drugi polinom

	status = readFileIntoList(P2, buffer);
	if (status != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	fclose(filePointer);

	return EXIT_SUCCESS;
}

int readFileIntoList(Position P, char* buffer)
{
	char* tempBuffer = buffer;
	int tempCoef = 0;
	int tempExp = 0;
	int noChar = 0;		// brojimo koliko char smo vec procitali u liniji
	int status = 0;
	Position newPolynome = NULL;

	while (strlen(tempBuffer) > 0)
	{
		status = sscanf(tempBuffer, " %dx^%d %n", &tempCoef, &tempExp, &noChar);
		if (status != 2)
		{
			printf("File read unsuccessfully\n");
			return EXIT_FAILURE;
		}

		newPolynome = createElement(tempCoef, tempExp);		// stvaramo novi element
		if (!newPolynome)
			return EXIT_FAILURE;

		insertSorted(P, newPolynome);

		tempBuffer += noChar;		// pomicemo pointer u liniji koju citamo
	}

	return EXIT_SUCCESS;
}

int insertSorted(Position P, Position newPolynome)
{
	Position current = P;

	while (current->Next != NULL && current->Next->Exponent > newPolynome->Exponent)
		current = current->Next;

	mergeElements(current, newPolynome);

	return EXIT_SUCCESS;
}

int mergeElements(Position current, Position newPolynome)
{
	if (current->Next == NULL || current->Next->Exponent != newPolynome->Exponent)
	{
		newPolynome->Next = current->Next;
		current->Next = newPolynome;
	}
	else
	{
		int newCoefficient = current->Next->Coefficient + newPolynome->Coefficient;
		Position delete = NULL;

		if (newCoefficient == 0)
		{
			delete = current->Next;
			current->Next = delete->Next;
			free(delete);
		}
		else
			current->Next->Coefficient = newCoefficient;

		free(newPolynome);
	}

	return EXIT_SUCCESS;
}

int connectList(Position P, Position newPolynome)
{
	Position current = P;

	while (P->Next != NULL)
	{
		P = P->Next;
	}
	newPolynome->Next = P->Next;
	P->Next = newPolynome;

	return EXIT_SUCCESS;
}

Position createElement(int coef, int exp)
{
	Position q = NULL;

	q = (Position)malloc(sizeof(Polynome));
	if (!q) {
		printf("Memory allocation unsuccessful\n");
		return MEM_ALLOC_FAIL;
	}

	q->Coefficient = coef;
	q->Exponent = exp;
	q->Next = NULL;

	return q;
}

int printPoly(char* polynomeName, Position first)
{
	printf(" %s = ", polynomeName);

	if (first) {
		if (first->Exponent < 0) {
			if (first->Coefficient == 1) {
				printf("x^(%d)", first->Exponent);
			}
			else {
				printf("%dx^(%d)", first->Coefficient, first->Exponent);
			}
		}
		else {
			if (first->Coefficient == 1) {
				printf("x^%d", first->Exponent);
			}
			else {
				printf("%dx^%d", first->Coefficient, first->Exponent);
			}
		}

		first = first->Next;
	}

	for (; first != NULL; first = first->Next) {
		if (first->Coefficient < 0) {
			if (first->Exponent < 0) {
				printf(" - %dx^(%d)", abs(first->Coefficient), first->Exponent);
			}
			else {
				printf(" - %dx^%d", abs(first->Coefficient), first->Exponent);
			}
		}
		else {
			if (first->Exponent < 0) {
				if (first->Coefficient == 1) {
					printf(" + x^(%d)", first->Exponent);
				}
				else {
					printf(" + %dx^(%d)", first->Coefficient, first->Exponent);
				}
			}
			else {
				if (first->Coefficient == 1) {
					printf(" + x^%d", first->Exponent);
				}
				else {
					printf(" + %dx^%d", first->Coefficient, first->Exponent);
				}
			}
		}
	}

	printf("\n");
	return EXIT_SUCCESS;
}

int insertNewElement(int coef, int exp, Position current)
{
	Position newElement = createElement(coef, exp);

	if (!newElement)
		return EXIT_FAILURE;

	newElement->Next = current->Next;
	current->Next = newElement;

	return EXIT_SUCCESS;
}

int polySum(Position PolySum, Position Poly1, Position Poly2)
{
	Position currentPoly1 = Poly1, currentPoly2 = Poly2, newElement = NULL;
	int coeff = 0;
	int exp = 0;

	while (currentPoly1 != NULL)
	{
		exp = currentPoly1->Exponent;
		coeff = currentPoly1->Coefficient;

		newElement = createElement(coeff, exp);
		sortedInput(PolySum, newElement);

		currentPoly1 = currentPoly1->Next;
	}

	while (currentPoly2 != NULL) {
		exp = currentPoly2->Exponent;
		coeff = currentPoly2->Coefficient;

		newElement = createElement(coeff, exp);
		sortedInput(PolySum, newElement);

		currentPoly2 = currentPoly2->Next;
	}

	return EXIT_SUCCESS;
}

int sortedInput(Position headPoly, Position newElement)
{
	Position current = headPoly;

	while (current->Next != NULL && newElement->Exponent < current->Next->Exponent)
		current = current->Next;

	if (current->Next == NULL || newElement->Exponent > current->Next->Exponent) {

		newElement->Next = current->Next;
		current->Next = newElement;
	}
	else
		mergeElements(current, newElement);

	return EXIT_SUCCESS;
}

int polyProduct(Position Poly1, Position Poly2, Position headPolyProduct)
{
	Position currentPoly1 = Poly1, currentPoly2 = Poly2, newElement = NULL;
	int coeff = 0, exp = 0;

	while (currentPoly1 != NULL)
	{
		while (currentPoly2 != NULL)
		{
			coeff = currentPoly1->Coefficient * currentPoly2->Coefficient;
			exp = currentPoly1->Exponent + currentPoly2->Exponent;

			newElement = createElement(coeff, exp);
			sortedInput(headPolyProduct, newElement);

			currentPoly2 = currentPoly2->Next;
		}

		currentPoly1 = currentPoly1->Next;
		currentPoly2 = Poly2;
	}

	return EXIT_SUCCESS;
}

int freeMemory(Position P)
{
	Position current = P;

	while (current->Next) {
		deleteAfter(current);
	}

	return EXIT_SUCCESS;
}

int deleteAfter(Position previous)
{
	Position toDelete = NULL;

	toDelete = previous->Next;
	previous->Next = toDelete->Next;
	free(toDelete);

	return EXIT_SUCCESS;
}