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

	printf("Choose an option:\n");
	printf("-----------------------");
	printf("1 - add to beginning\n");
	printf("2 - print list\n");
	printf("3 - add to end\n");
	printf("4 - find by last name\n");
	printf("5 - delete element\n");
	printf("6 - exit");
	printf("-----------------------");
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		printf("Add to beginning:\n");		// done ish
		addToBeginning(P);
		break;

	case 2:
		printf("Print list:\n");		// done ish
		PrintList(P->next);
		break;

	case 3:
		printf("Add to end:\n");		// done ish
		addToEnd(P->next);
		break;

	case 4:
		printf("Find by last name:\n");		// done ish
		person = findByLastName(P->next);
		person ? printPerson(person) : printf("cant find person\n");
			break;

	case 5:
		printf("Delete person:\n");		// done ish but i think it doesnt work idk
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

Position createPerson()
{
	Position newPerson = NULL;
	char nameTemp[MAX_LENGTH] = { 0 };
	char lastNameTemp[MAX_LENGTH] = { 0 };
	int birthYearTemp = 0;

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

int addToBeginning(Position P)
{
	Position q = NULL;
	q = createPerson();

	q->next = P->next;
	P->next = q;

	return 0;
}

int PrintList(Position P)
{
	while (P != NULL)
	{
		printf("\nPerson:\n");
		printf("\tName: \033[1; 32m%s\033[0m\n", P->name);
		printf("\tLast name: \033[1; 32m%s\033[0m\n", P->lastn);
		printf("\tName: \033[1; 32m%d\033[0m\n", P->birthYear);

		P = P->next;
	}
	return 0;
}

int addToEnd(Position P)		// not like from lab ??? test it
{
	Position q = NULL;
	q = createPerson();

	while (P->next != NULL)
		P = P->next;

	q->next = P->next;
	P->next = q;

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

	scanf("Enter last name:\n");
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

	return PERSON_NOT_FOUND;
}

int deleteElement(Position P)
{
	Position current = P;
	char lastNameTemp[MAX_LENGTH] = { 0 };

	scanf("Enter last name:\n");
	scanf("%s", lastNameTemp);

	if (P->next)
	{
		Position previous = NULL;

		while (current->next && strcmp(current->lastn, lastNameTemp) != 0)
		{
			previous = current;
			current = current->next;
		}

		if (previous && previous->next && strcmp(current->lastn, lastNameTemp) == 0)
		{
			printPerson(current);
			previous->next = current->next;
			free(current);
		}
	}
	else
		return PERSON_NOT_FOUND;		// mislim da ne valja else fale jos 2 elsea

	/*Position temp;

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

	return 0;*/
}
