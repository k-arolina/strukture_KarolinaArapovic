/* TRECI ZADATAK */

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



int main()
{

	// isto fja menu kao i u drugom zadatku

	return 0;
}

int findPrev()				// saljem head !!NE &head!!
{
	// opet char surname i strcpy kao i u proslim funkcijama.......
}


int insertAfterPerson(Position person)
{
	Position newperson = NULL;

	newperson = createperson();

	if (newperson)
	{
		newperson->next = person->next;
		person->next = newperson;
	}

	reutrn EXIT_SUCCESS;
}

int bubbleSort(Position firstItem)		//koristi swapitems
{
	int swapped = 0;
	Position lastPersonRead = NULL;

	// ako lista nema el ilii ima samo jedan eelment izlazimo iz funkcije
}

int swapItems(Position first, Position second)
{
	//zamjeni vrijednosti first i second za name surname i year

	return EXIT_SUCCESS;
}