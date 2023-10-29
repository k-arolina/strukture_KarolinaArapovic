<<<<<<< HEAD
// OLD CODE



/*  2. Definirati strukturu osoba (ime, prezime, godina rodjenja) i napisati program koji:
A. dinamicki dodaje novi element na pocetak liste,
B. ispisuje listu,
C. dinamicki dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. brise odredjeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.  */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX_LENGTH 1024
#define FILE_NOT_OPEN -1
#define ALLOC_FAIL -2

struct _Person;
typedef struct _Person* Position;
typedef struct _Person
{
	char name[MAX_LENGTH];
	char lastn[MAX_LENGTH];
	int birthYear;
	Position next;
} Person;

int addToBeginning(Position P);
int PrintList(Position P);
int addToEnd(Position P);
Position findByLastName(Position P, char X[MAX_LENGTH]);
int deleteElement(Position P, char X[MAX_LENGTH]);

int main()
{
	int n = 0, i = 0;
	Person Head;
	char lastName[MAX_LENGTH] = { 0 };

	Head.next = NULL;

	printf("How many elements to add? ");
	scanf("%d", &n);

	for (i = 0; i < n; i++)
	{
		printf("Add to beginning\n");
		printf("\nEnter element no.%d:\n", i+1);
		addToBeginning(&Head);
	}

	for (i = 0; i < n; i++)
	{
		printf("Add to end\n");
		printf("\nEnter element no.%d:\n", i + 1);
		addToEnd(Head.next);
	}


	PrintList(Head.next);


	printf("Enter last name to search: ");
	scanf("%s", lastName);

	if (findByLastName(Head.next, lastName))
		printf("\nLast name exists");
	else
		printf("\nLast name does not exist");


	printf("Enter last name to delete: ");
	scanf("%s", lastName);

	deleteElement(&Head, lastName);


	PrintList(Head.next);

	return 0;
}


int addToBeginning(Position P)
{
	Position q;

	q = (Position)malloc(sizeof(Person));

	printf("Enter name: ");
	scanf("%s", q->name);
	printf("Enter last name: ");
	scanf("%s", q->lastn);
	printf("Enter birth year: ");
	scanf("%d", &q->birthYear);
	printf("\n");

	q->next = P->next;
	P->next = q;

	return 0;
}

int PrintList(Position P)
{
	while (P != NULL)
	{
		printf("\nPerson:\n");
		printf("\tName: %s\n", P->name);
		printf("\tLast name: %s\n", P->lastn);
		printf("\tName: %d\n", P->birthYear);

		P = P->next;
	}
	return 0;
}

int addToEnd(Position P)
{
	Position q;

	q = (Position)malloc(sizeof(Person));

	printf("Enter name: ");
	scanf("%s", q->name);
	printf("Enter last name: ");
	scanf("%s", q->lastn);
	printf("Enter birth year: ");
	scanf("%d", &q->birthYear);
	printf("\n");

	while (P->next != NULL)
		P = P->next;

	q->next = P->next;
	P->next = q;

	return 0;
}

Position findByLastName(Position P, char X[MAX_LENGTH])
{
	while (P != NULL && P->lastn != X)
		P = P->next;

	// problem here somewh

	printf("%s", P->lastn);

	return P;
}

int deleteElement(Position P, char X[MAX_LENGTH])	// didnt test this yet
{
	Position temp;

	while (P->next != NULL && P->next->lastn != X)
		P = P->next;

	if (P->next == NULL)
		P = NULL;
	else
		P = P;

	if (P != NULL)
	{
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}

	return 0;
}
=======
/*  2. Definirati strukturu osoba (ime, prezime, godina rodjenja) i napisati program koji:
A. dinamicki dodaje novi element na pocetak liste,
B. ispisuje listu,
C. dinamicki dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. brise odredjeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.  */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX_LENGTH 1024
#define FILE_NOT_OPEN -1
#define ALLOC_FAIL -2

struct _Person;
typedef struct _Person* Position;
typedef struct _Person
{
	char name[MAX_LENGTH];
	char lastn[MAX_LENGTH];
	int birthYear;
	Position next;
} Person;

int addToBeginning(Position P);
int PrintList(Position P);
int addToEnd(Position P);
Position findByLastName(Position P, char X[MAX_LENGTH]);
int deleteElement(Position P, char X[MAX_LENGTH]);

int main()
{
	int n = 0, i = 0;
	Person Head;
	char lastName[MAX_LENGTH] = { 0 };

	Head.next = NULL;

	printf("How many elements to add? ");
	scanf("%d", &n);

	for (i = 0; i < n; i++)
	{
		printf("Add to beginning\n");
		printf("\nEnter element no.%d:\n", i+1);
		addToBeginning(&Head);
	}

	for (i = 0; i < n; i++)
	{
		printf("Add to end\n");
		printf("\nEnter element no.%d:\n", i + 1);
		addToEnd(Head.next);
	}


	PrintList(Head.next);


	printf("Enter last name to search: ");
	scanf("%s", lastName);

	if (findByLastName(Head.next, lastName))
		printf("\nLast name exists");
	else
		printf("\nLast name does not exist");


	printf("Enter last name to delete: ");
	scanf("%s", lastName);

	deleteElement(&Head, lastName);


	PrintList(Head.next);

	return 0;
}


int addToBeginning(Position P)
{
	Position q;

	q = (Position)malloc(sizeof(Person));

	printf("Enter name: ");
	scanf("%s", q->name);
	printf("Enter last name: ");
	scanf("%s", q->lastn);
	printf("Enter birth year: ");
	scanf("%d", &q->birthYear);
	printf("\n");

	q->next = P->next;
	P->next = q;

	return 0;
}

int PrintList(Position P)
{
	while (P != NULL)
	{
		printf("\nPerson:\n");
		printf("\tName: %s\n", P->name);
		printf("\tLast name: %s\n", P->lastn);
		printf("\tName: %d\n", P->birthYear);

		P = P->next;
	}
	return 0;
}

int addToEnd(Position P)
{
	Position q;

	q = (Position)malloc(sizeof(Person));

	printf("Enter name: ");
	scanf("%s", q->name);
	printf("Enter last name: ");
	scanf("%s", q->lastn);
	printf("Enter birth year: ");
	scanf("%d", &q->birthYear);
	printf("\n");

	while (P->next != NULL)
		P = P->next;

	q->next = P->next;
	P->next = q;

	return 0;
}

Position findByLastName(Position P, char X[MAX_LENGTH])
{
	while (P != NULL && P->lastn != X)
		P = P->next;

	// problem here somewh

	printf("%s", P->lastn);

	return P;
}

int deleteElement(Position P, char X[MAX_LENGTH])	// didnt test this yet
{
	Position temp;

	while (P->next != NULL && P->next->lastn != X)
		P = P->next;

	if (P->next == NULL)
		P = NULL;
	else
		P = P;

	if (P != NULL)
	{
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}

	return 0;
}
>>>>>>> 5c05faed82b84068df544e3205f9ae7f4b899640
