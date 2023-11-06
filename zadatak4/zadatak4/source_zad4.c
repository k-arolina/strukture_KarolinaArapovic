/* 4. Napisati program za zbrajanje i mnozenje polinoma. Koeficijenti i eksponenti se
citaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nuzno sortirani. */

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

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
//int polySum();
//int polyMultiply();

int main()
{
	Polynome headPoly1 = { .Coefficient = 0, .Exponent = 0, .Next = NULL };
	Polynome headPoly2 = { .Coefficient = 0, .Exponent = 0, .Next = NULL };

	if (readPoly(&headPoly1, &headPoly2) == EXIT_SUCCESS)
	{
		printf("File read successfully!\n\n");
		printf("First polynome:\n");
		printPoly(headPoly1.Next);		// ne radi jer je headPoly1.Next == NULL ???
		printf("Second polynome:\n");
		printPoly(headPoly2.Next);
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
		status = sscanf(tempBuffer, " %dx^%d %n", &tempCoef, &tempExp, &noChar);	// ucitava vrijednosti iz dat u varijable
		if (status != 2)		// sscanf !2 jer vraca broj varijabli koje je procitao, %n se ne broji kao varijabla ?
		{
			printf("File read unsuccessfully\n");
			return EXIT_FAILURE;
		}

		newPolynome = createElement(tempCoef, tempExp);		// stvaramo novi element
		if (!newPolynome)
			return EXIT_FAILURE;

		//connectList(P, newPolynome);

		tempBuffer += noChar;		// pomicemo pointer u liniji koju citamo
	}

	return EXIT_SUCCESS;
}

/*int connectList(Position P, Position newPolynome)
{
	Position current = P;

	while (current->Next != NULL && current->Next->Exponent > newPolynome->Exponent)
		current = current->Next;

	return EXIT_SUCCESS;
}*/

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
	if (P)		// ne printa jer je P = NULL ??? kako cu uvezati elemente ???
	{
		if (P->Coefficient == 1)
			printf("x^%d ", P->Exponent);
		else
			printf("%dx^%d ", P->Coefficient, P->Exponent);

		P = P->Next;
	}

	printf("\n");
	return EXIT_SUCCESS;
}

