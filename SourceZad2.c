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
#define PERSON_NOT_FOUND -1
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

int menu(Position P);
Position createPerson();
int addToBeginning(Position P);
int PrintList(Position P);
int addToEnd(Position P);
Position findByLastName(Position P);
int deleteElement(Position P);
void printPerson(Position P);

int main()
{
	Person Head = { .name = 0, .lastn = 0, .birthYear = 0, .next = NULL };

	menu(&Head);

	return 0;
}

int menu(Position P)
{
	Position person;
	int choice;

	printf("\nChoose an option:\n");
	printf("-----------------------\n");
	printf("1 - add to beginning\n");
	printf("2 - add to end\n");
	printf("3 - print list\n");
	printf("4 - find by last name\n");
	printf("5 - delete element\n");
	printf("6 - exit\n");
	printf("-----------------------\n");
	scanf("%d", &choice);
	printf("\n");

	switch (choice)
	{
	case 1:
		printf("Add to beginning:\n");
		addToBeginning(P);
		break;

	case 2:
		printf("Add to end:\n");
		addToEnd(P->next);
		break;
		
	case 3:
		printf("Print list:\n");
		PrintList(P->next);
		break;

	case 4:
		printf("Find by last name:\n");
		person = findByLastName(P->next);		// radi osim ako ne postoji prezime ???
		if (person)
			printPerson(person);
		break;

	case 5:
		printf("Delete person:\n");		// radi ali ne printa not found ???
		deleteElement(P);
		break;

	case 6:
		printf("Exit\n");
		return 0;
		break;

	default:
		printf("Error! Enter your choice again:\n");
		break;
	}

	return menu(P);
}

Position createPerson()		// stvara novi pointer na strukturu tipa person
{
	Position newPerson = NULL;
	char nameTemp[MAX_LENGTH] = { 0 };
	char lastNameTemp[MAX_LENGTH] = { 0 };

	newPerson = (Position)malloc(sizeof(Person));

	printf("Enter name:\n");
	scanf("%s", nameTemp);
	printf("Enter last name:\n");
	scanf("%s", lastNameTemp);
	printf("Enter birth year:\n");
	scanf(" %d", &newPerson->birthYear);

	strcpy(newPerson->name, nameTemp);
	strcpy(newPerson->lastn, lastNameTemp);

	return newPerson;
}

int addToBeginning(Position P)		// dodaje novi element na pocetak liste
{
	Position q = NULL;
	q = createPerson();		// koristimo funckiju createPerson da ne pisemo isto vise puta

	q->next = P->next;
	P->next = q;

	return 0;
}

int addToEnd(Position P)		// dodaje novi element na kraj liste
{
	Position q = NULL;
	q = createPerson();

	while (P->next != NULL)
		P = P->next;

	q->next = P->next;
	P->next = q;

	return 0;
}

int PrintList(Position P)		// ispisuje listu
{
	while (P != NULL)
	{
		printf("\nPerson:\n");					// kako formatirati boju ???
		printf("\tName: %s\n", P->name);
		printf("\tLast name: %s\n", P->lastn);
		printf("\tBirth year: %d\n", P->birthYear);

		P = P->next;
	}
	return 0;
}

Position findByLastName(Position P)
{
	Position current = P;
	char lastNameTemp[MAX_LENGTH] = { 0 };

	if (!P)
	{
		printf("Empty list\n");
		return PERSON_NOT_FOUND;
	}

	printf("\nEnter last name to search:\n");
	scanf("%s", lastNameTemp);

	do {
		if (strcmp(current->lastn, lastNameTemp) == 0)
		{
			return current;
		}
		else {
			current = current->next;
		}
	} while (current);

	printf("Person not found!\n");		// crasha ako je person not found ???
	return PERSON_NOT_FOUND;
}

void printPerson(Position P)
{
	printf("\n");
	printf("Name: %s\n", P->name);
	printf("Last name: %s\n", P->lastn);
	printf("Birth year: %d\n", P->birthYear);
}

int deleteElement(Position P)
{
	Position q = P;
	Position prev = NULL;
	char lastNameTemp[MAX_LENGTH] = { 0 };

	printf("\nEnter last name to delete:\n");
	scanf("%s", lastNameTemp);

	if (P->next) {
		while (q->next && strcmp(q->lastn, lastNameTemp) != 0) {
			prev = q;
			q = q->next;
		}
		if (prev && prev->next && strcmp(q->lastn, lastNameTemp) == 0) {
			printPerson(q);
			prev->next = q->next;
			free(q);
		}
	}
	else
		printf("Person not found!");		// ne printa person not found ???
		return PERSON_NOT_FOUND;
}
