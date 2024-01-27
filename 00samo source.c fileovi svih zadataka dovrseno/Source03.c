/* 3. Prethodnom zadatku dodati funkcije:
A. dinamicki dodaje novi element iza odredjenog elementa,
B. dinamicki dodaje novi element ispred odredjenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. cita listu iz datoteke. */


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX_LENGTH 1024
#define PERSON_NOT_FOUND -1
#define FILE_NOT_OPEN -1
#define	EMPTY_LIST -1
#define ALLOC_FAIL -2
#define EXIT_SUCCESS 0
#define NO_PERSON_FOUND_INT -2
#define SINGLE_PERSON_IN_LIST -3


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
int printPerson(Position P);
int PrintList(Position P);
int addToEnd(Position P);
Position findByLastName(Position P);
int deleteElement(Position P);


// funkcije za treci zad.

Position Search(Position P, char lastName[MAX_LENGTH]);
int insertAfterPerson(Position P);
int findPrev(Position P, char lastName[MAX_LENGTH]);
int insertBeforePerson(Position P);
int swapItems(Position first, Position second);
int bubbleSort(Position P);		// sortira po prezimenu
int writeListToFile(Position P);
int readFromFileToList(Position* P);
int addPerson(Position* P, const char* tempName, const char* tempLast, int birthYear);

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
	printf("2 - print list\n");
	printf("3 - add to end\n");
	printf("4 - find by last name\n");
	printf("5 - delete element\n");
	printf("-----------------------\n");
	printf("6 - insert after person\n");
	printf("7 - insert before person\n");
	printf("8 - sort by last name\n");
	printf("9 - write list to file\n");
	printf("9 - make list from file\n");
	printf("-----------------------\n");
	printf("11 - exit\n");
	printf("-----------------------\n");
	scanf("%d", &choice);
	printf("\n");

	switch (choice)
	{
	case 1:
		printf("\nAdd to beginning:\n");
		addToBeginning(P);
		break;

	case 2:
		printf("\nPrint list:\n");
		PrintList(P->next);
		break;

	case 3:
		printf("\nAdd to end:\n");
		addToEnd(P->next);
		break;

	case 4:
		printf("\nFind by last name:\n");
		person = findByLastName(P->next);

		if (person == NULL)
			printf("Person not found\n");
		else
			printPerson(person);

		break;

	case 5:
		printf("\nDelete person:\n");
		deleteElement(P);
		break;

/////////////////////////////////////////////////////////////////////////////

	case 6:
		printf("Insert after person:\n");		// done
		insertAfterPerson(P);
		break;

	case 7:
		printf("Insert before person:\n");		// done
		insertBeforePerson(P);
		break;

	case 8:
		printf("Sort by last name:\n");			// done
		bubbleSort(P);
		break;

	case 9:
		printf("Write list to file\n");			// done
		writeListToFile(P);
		break;

	case 10:
		printf("Make list from file\n");		// done
		readFromFileToList(P);
		break;

	case 11:
		printf("\nExit\n");
		return 0;
		break;

	default:
		printf("\nError! Enter your choice again:\n");
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

	if (newPerson == NULL)		// provjera
	{
		printf("Unsuccessful memory alloc. in function newPerson\n");
		return ALLOC_FAIL;
	}

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

int printPerson(Position P)		// ispisuje samo jednu osobu
{
	if (P != NULL)
	{
		printf("\nPerson:\n");
		printf("\tName: \033[1; 32m%s\033[0m\n", P->name);
		printf("\tLast name: \033[1; 32m%s\033[0m\n", P->lastn);
		printf("\tBirth year: \033[1; 32m%d\033[0m\n", P->birthYear);
	}
	return 0;
}

int PrintList(Position P)
{
	while (P != NULL)
	{
		printf("\nPerson:\n");
		printf("\tName: \033[1; 32m%s\033[0m\n", P->name);
		printf("\tLast name: \033[1; 32m%s\033[0m\n", P->lastn);
		printf("\tBirth year: \033[1; 32m%d\033[0m\n", P->birthYear);

		P = P->next;
	}
	return 0;
}

int addToEnd(Position P)
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

	return NULL;
}

int deleteElement(Position P)
{
	Position current = P;
	char lastNameTemp[MAX_LENGTH] = { 0 };

	scanf("Enter last name to delete:\n");
	scanf("%s", lastNameTemp);

	if (P->next)
	{
		Position previous = NULL;

		while (current->next && strcmp(current->lastn, lastNameTemp) != 0)		// dok je sljedeci razlicit od null i nisu ista prezimena
		{
			previous = current;
			current = current->next;		// dodje ili do kraja liste ili do elementa kojeg trazimo
		}

		if (strcmp(current->lastn, lastNameTemp) == 0)
		{
			previous->next = current->next;
			free(current);
		}
		else
			printf("Person not found\n");
	}
	else
		return PERSON_NOT_FOUND;
}


////////////////////
// FUNKCIJE ZA 3. //
////////////////////

Position Search(Position P, char lastName[MAX_LENGTH])		// trazi element sa odredjenim prezimenom
{
	while (P != NULL && strcmp(P->lastn, lastName) == 0)
		P = P->next;

	return P;
}

int insertAfterPerson(Position P)
{
	Position q;
	char lastName[MAX_LENGTH] = { 0 };

	if (!P)
	{
		printf("Empty list!\n");
		return PERSON_NOT_FOUND;
	}

	printf("\nEnter last name:\n");
	scanf("%s", lastName);

	P = Search(P->next, lastName);

	if (P != NULL)
	{
		q = createPerson();

		q->next = P->next;
		P->next = q;
	}

	return EXIT_SUCCESS;
}

int findPrev(Position P, char lastName[MAX_LENGTH])
{
	while (P->next != NULL && strcmp(P->lastn, lastName) == 0)
		P = P->next;

	if (P->next == NULL)
		return NULL;
	else
		return P;
}

int insertBeforePerson(Position P)
{
	Position q;
	char lastName[MAX_LENGTH] = { 0 };

	if (!P)
	{
		printf("Empty list!\n");
		return PERSON_NOT_FOUND;
	}

	printf("\nEnter last name:\n");
	scanf("%s", lastName);

	P = findPrev(P, lastName);

	if (P != NULL)
	{
		q = createPerson();

		q->next = P->next;
		P->next = q;
	}

	return EXIT_SUCCESS;
}

int swapItems(Position first, Position second)
{
	char tempName[MAX_LENGTH];
	char tempSurname[MAX_LENGTH];
	int tempBirthYear;

	strcpy(tempName, first->name);
	strcpy(tempSurname, first->lastn);
	tempBirthYear = first->birthYear;

	strcpy(first->name, second->name);
	strcpy(first->lastn, second->lastn);
	first->birthYear = second->birthYear;

	strcpy(second->name, tempName);
	strcpy(second->lastn, tempSurname);
	second->birthYear = tempBirthYear;

	return EXIT_SUCCESS;
}

int bubbleSort(Position P)		// sortira po prezimenu
{
	int swapped = 0;
	Position lastPersonRead = NULL;
	Position start = P;

	if (!P) {
		printf("Empty list!\n");
		return NO_PERSON_FOUND_INT;
	}
	else if (!P->next) {
		printf("Only single element in list!\n");
		return SINGLE_PERSON_IN_LIST;
	}

	do {
		swapped = 0;
		Position current = start;

		while (current->next != lastPersonRead) {
			if (strcmp(current->lastn, current->next->lastn) > 0) {
				swapItems(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		lastPersonRead = current;
	} while (swapped);

	return EXIT_SUCCESS;
}

int writeListToFile(Position P)
{
	FILE* filePointer = fopen("list.txt", "w");

	if (filePointer == NULL) {
		printf("Could not open file\n");
		return FILE_NOT_OPEN;
	}

	while (P != NULL) {
		fprintf(filePointer, "Name: %s\nLast name: %s\nBirth Year: %d\n\n", P->name, P->lastn, P->birthYear);
		P = P->next;
	}

	fclose(filePointer);

	return EXIT_SUCCESS;
}

int readFromFileToList(Position* P)
{
	FILE* filePointer = fopen("list.txt", "r");

	if (filePointer == NULL) {
		printf("Could not open file\n");
		return FILE_NOT_OPEN;
	}

	char tempName[MAX_LENGTH];
	char tempLast[MAX_LENGTH];
	int birthYear;

	while (fscanf(filePointer, "Name: %s\nLast name: %s\nBirth Year: %d\n\n", tempName, tempLast, &birthYear) == 3) {
		addPerson(P, tempName, tempLast, birthYear);
	}

	fclose(filePointer);
	return EXIT_SUCCESS;
}

int addPerson(Position* P, const char* tempName, const char* tempLast, int birthYear)
{
	Position newPerson = (Position)malloc(sizeof(Person));

	if (newPerson == NULL) {
		printf("Could not allocate memory\n");
		return ALLOC_FAIL;
	}

	strcpy(newPerson->name, tempName);
	strcpy(newPerson->lastn, tempLast);
	newPerson->birthYear = birthYear;

	newPerson->next = *P;
	*P = newPerson;

	return EXIT_SUCCESS;
}