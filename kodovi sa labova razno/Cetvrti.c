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

int readPoly(Position P1, Position P2);				// cita polinom iz datoteke
int readFileIntoList(Position P, char* buffer);		// sadrzaj datoteke ucitava u listu
Position createElement(int coef, int exp);			// stvara novi element
int printPoly(Position P);
int connectList(Position P, Position newPolynome);
int deleteAfter(Position prev);
int polySum(Position PolySum, Position Poly1, Position Poly2);
int insertNewElement(Position current, int coef, int exp);
int MultiplyPoly(Position PolyMult, Position Poly1, Position Poly2);

int main()
{
	Polynome headPoly1 = { .Coefficient = 0, .Exponent = 0, .Next = NULL };
	Polynome headPoly2 = { .Coefficient = 0, .Exponent = 0, .Next = NULL };
	Polynome headPolySum= { .Coefficient = 0, .Exponent = 0, .Next = NULL };
	Polynome headMultiply = { .Coefficient = 0, .Exponent = 0, .Next = NULL };;


	if (readPoly(&headPoly1, &headPoly2) == EXIT_SUCCESS)
	{
		printf("File read successfully!\n\n");
		printf("First polynome:\n");
		printPoly(headPoly1.Next);		
		printf("Second polynome:\n");
		printPoly(headPoly2.Next);
	}
	polySum(&headPolySum, headPoly1.Next, headPoly2.Next);
	printf("Polynome sum:\n");
	printPoly(headPolySum.Next);

	MultiplyPoly(&headMultiply, headPoly1.Next, headPoly2.Next);		
	printf("Polynome multiply:\n");
	printPoly(headMultiply.Next);




	return 0;
}

int readPoly(Position P1, Position P2)
{
	FILE* filePointer;
	char buffer[MAX_LENGTH] = { 0 };
	int status = EXIT_SUCCESS;

	filePointer = fopen("polynome.txt", "r");
	if (!filePointer) {
		printf("File open unsuccessful\n");
		return FILE_NOT_OPEN;

	}
	perror;

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

	while (strlen(tempBuffer) > 0)		// samo cita prvi element polinoma ???
	{
		status = sscanf(tempBuffer, " %dx^%d %n", &tempCoef, &tempExp, &noChar);	// ucitava vrijednosti iz dat u varijable
		if (status != 2)		// sscanf !2 jer vraca broj varijabli koje je procitao, %n se ne broji kao varijabla ?
		{
			printf("File read unsuccessfully\n");
			return EXIT_FAILURE;
		}

		newPolynome = createElement(tempCoef, tempExp);		// stvaramo novi element
		if (!newPolynome)
			return EXIT_FAILURE;

		connectList(P, newPolynome);

		tempBuffer += noChar;		// pomicemo pointer u liniji koju citamo
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
	return EXIT_SUCCESS;
}
int deleteAfter(Position prev) {
	Position toDelete = NULL;

	toDelete = prev->Next;
	prev->Next = toDelete->Next;
	free(toDelete);

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

int printPoly(Position P)
{
	if (P == NULL)
		printf("There is no polynomial.\n");
	else {

		while (P != NULL) {

			printf("(%dx^%d)", P->Coefficient, P->Exponent);
			P = P->Next;

			if (P != NULL)
				printf(" + ");
			else
				printf("\n");
		}
	}
	return 0;

}
int insertNewElement(Position current, int coef, int exp)
{
	Position newElement = createElement(coef, exp);

	if (!newElement)
		return EXIT_FAILURE;

	while (current->Next != NULL && current->Next->Exponent > exp)
		current = current->Next;

	if (current->Next != NULL && current->Next->Exponent == exp) {
		current->Next->Coefficient += coef;
	}
	else {
		
		newElement->Next = current->Next;
		current->Next = newElement;
	}
	

	return EXIT_SUCCESS;
}

int polySum(Position PolySum, Position Poly1, Position Poly2)
{
	Position tempPoly;

	while (Poly1 != NULL && Poly2 != NULL)
	{
		if (Poly1->Exponent == Poly2->Exponent)
		{
			insertNewElement(PolySum, Poly1->Coefficient + Poly2->Coefficient, Poly1->Exponent);
			Poly1 = Poly1->Next;
			Poly2 = Poly2->Next;
		}
		else if (Poly1->Exponent > Poly2->Exponent)
		{
			insertNewElement(PolySum, Poly1->Coefficient, Poly1->Exponent);
			Poly1 = Poly1->Next;
		}
		else
		{
			insertNewElement(PolySum, Poly2->Coefficient, Poly2->Exponent);
			Poly2 = Poly2->Next;
		}
	}

	if (Poly1 != NULL)
		tempPoly = Poly1;
	else
		tempPoly = Poly2;

	while (tempPoly != NULL)
	{
		insertNewElement(PolySum, tempPoly->Coefficient, tempPoly->Exponent);
		tempPoly = tempPoly->Next;
	}

	/*Position currentPoly1 = Poly1;
	Position currentPoly2 = Poly2;
	Position currentSum = PolySum;
	Position remainingPoly = NULL;

	while (currentPoly1 != NULL && currentPoly2 != NULL) {
		if (currentPoly1->Exponent == currentPoly2->Exponent) {
			insertNewElement(currentPoly1->Coefficient + currentPoly2->Coefficient, currentPoly1->Exponent, currentSum);		// stvaramo novi element koji je zbroj elemenata iz prva dva polinoma
			currentPoly1 = currentPoly1->Next;
			currentPoly2 = currentPoly2->Next;
			currentSum = currentSum->Next;		// pomicemo poziciju svih polinoma na sljedeci element
		}
		else if (currentPoly1->Exponent < currentPoly2->Exponent) {
			insertNewElement(currentPoly1->Coefficient, currentPoly1->Exponent, currentSum);
			currentPoly1 = currentPoly1->Next;
			currentSum = currentSum->Next;
		}
		else {
			insertNewElement(currentPoly2->Coefficient, currentPoly2->Exponent, currentSum);
			currentPoly2 = currentPoly2->Next;
			currentSum = currentSum->Next;
		}

	}
	if (currentPoly1 == NULL)
		remainingPoly = currentPoly2;
	else
		remainingPoly = currentPoly1;

	while (remainingPoly != NULL) {
		insertNewElement(remainingPoly->Coefficient, remainingPoly->Exponent, currentSum);
		remainingPoly = remainingPoly->Next;
		currentSum = currentSum->Next;
	}*/

	return EXIT_SUCCESS;
}
int MultiplyPoly(Position PolyMult, Position Poly1, Position Poly2) {

	Position current = Poly2;
	while (Poly1 != NULL) {
		while (Poly2 != NULL) {
			insertNewElement(PolyMult, Poly1->Coefficient * Poly2->Coefficient, Poly1->Exponent + Poly2->Exponent);
			Poly2 = Poly2->Next;
		}
		Poly1 = Poly1->Next;
		Poly2 = current;

	}
	return EXIT_SUCCESS;
}