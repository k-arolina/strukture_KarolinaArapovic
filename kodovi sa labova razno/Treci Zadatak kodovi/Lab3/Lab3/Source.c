/* DRUGI ZADATAK */


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
	char surname[MAX_LENGTH];
	int birthYear;
	Position next;
} Person;




Position findLast(Position head)		// saljemo &Head
{
	Position current = head;

	while (current->next != NULL)		// moze i bez != NULL
	{
		current = current->next;
	}

	return current;
}

int addToEnd(Position head)
{
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = createPerson();

	while (newPerson)				// while?????? ne znam koja je petlja
	{
		last = findLast(head);
		newPerson->next = last->next;
		last->next = newPerson;
	}
}


int ispisListe(Position firstItem)		// saljemo head next
{
	Position current = firstItem;

	if (!firstItem)
	{
		printf("Empty list");

		while (current)			// ispisuje element sve dok on nije nula
		{
			printPerson(current);
			current = current->next;
		}

		return EXIT_SUCCESS;
	}
}

int printperson(Position person)
{
	printf("%s %s %d %d", person->name, person->surname/*...........*/);

		return EXIT_SUCCESS;
}

Position findPersonByLastName(Position firstItem)	// saljem head next

// u mainu iza poziva ide:::::      person ? printPerson(person) : printf("cant find person);

{
	Position current = firstItem;
	char surname[MAX_LENGTH] = { 0 };

	if (!firstItem)
	{
		printf("empty list");
		return PERSON_NOT_FOUND;		// treba dodat u define
	}

	strcpy(surname, enterSurname());		// enterSurname je samo scanf surname i vraca surname

	//surname = enterSurname(); ----> ne koristimo jer pointeri or whatever idk ---> surname je pokazivac na pocetak niza tj to je samo adresa

	do {
		if (strcmp(current->surname, surname) == 0)		// strcmp jer je surname lokacij u memoriji pa ne mozemo samo njega usporedjivat
		{
			return current;
		}
		else {
			current = current->next;
		}
	} while (current);

	return PERSON_NOT_FOUND;
}


int deletePerson(Position head)				// saljemo samo head   !!! NE &head !!!
{
	Position current = head;
	char surname[MAX_LENGTH] = { 0 };

	strcpy(surname, enterSurname());
	if (head->next)
	{
		Position previous = NULL;

		while (current->next && strcmp(current->surname, surname) != 0)
		{
			previous = current;
			current = current->next;
		}

		if (previous && previous->next && strcmp(current->surname, surname) == 0)		// previous na pocetku jer intellisence dumb // NE ZNAM jel ==0 ili !=0 //
		{
			printPerson(current);
			previous->next = current->next;
			free(current);		// oslobadja memoriju
		}
	}
	else
		return No_PERSON_FOUND_INT;		// mislim da ne valja else fale jos 2 elsea
}


int main()
{
	Person head = { .next = NULL };		//.... sve inicijalizirat na 0

	menu(&head);

	return 0;
}

// napravi menu fju koja dopusta odabir operacije

int menu(/*.........???'*/)
{
	// menu je rekurzivna fja ??? nakon svake operacije opet se prikaze menu
	// printf format colors ???
}