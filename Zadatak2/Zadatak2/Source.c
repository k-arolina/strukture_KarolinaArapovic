#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LENGTH 1024
#define PERSON_NOT_FOUND -1
typedef struct person Person;
typedef struct person* Position;

struct person {
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int birth_year;
	Position next;

};
Position createPerson();
int AddToFront(Position p);
int PrintTheList(Position p);
int AddToEnd(Position p);
Position FindBySurname(Position p, char surname);
int DeletePerson(Position p, char surname);


int main()
{
	Person Head;
	Person trazena_osoba;
	Head.next = NULL;

	menu(&Head);

	return 0;

}
Position createPerson() {
	Position New_Person = NULL;
	char ime[MAX_LENGTH] = { 0 };
	char prezime[MAX_LENGTH] = { 0 };
	int god_rod = 0;

	New_Person = (Position)malloc(sizeof(Person));

	printf("Unesi ime:\n");
	scanf("%s", ime);
	printf("Unesi prezime:\n");
	scanf("%s", prezime);
	printf("Unesi godinu rodenja:\n");
	scanf(" %d", &New_Person->birth_year);

	strcpy(New_Person->name, ime);
	strcpy(New_Person->surname, prezime);


	return New_Person;
}

int AddToFront(Position p) {
	Position np = NULL;
	np = createPerson();


	np->next = p->next;
	p->next = np;

	return 0;
}
int PrintTheList(Position p) {
	while (p != NULL) {
		printf("\nPerson:\n");
		printf("\tName: %s\n", p->name);
		printf("\tLast name: %s\n", p->surname);
		printf("\tName: %d\n", p->birth_year);

		p = p->next;
	}
}
//int PrintTheList(Position p) {
//
//	Position np = p;//np=newperson
//	if (!p) {
//		printf("Empty list.\n");
//	}
//	while (np) {
//		printPerson(np);
//		np = np->next;
//	}
//	return 0;
//
//}
int printPerson(Position p) {

	printf("%s", p->name);
	printf("%s", p->surname);
	printf(" %d", p->birth_year);


	return 0;

}
int AddToEnd(Position p) {
	Position np = NULL;
	np = createPerson();

	while (np->next != NULL) {
		np = np->next;
	}
	if (np) {//nisan sig za if
		np->next = p->next;
		p->next = np;
	}
	return 0;
}
Position FindBySurname(Position p, char prezime) {
	Position Np = NULL;


	Np = createPerson();
	while (Np != NULL) {
		if (strcmp(Np->surname, prezime) == 0) {
			return Np;
		}
		else {
			Np = Np->next;
		}

	}
	return PERSON_NOT_FOUND;

}
int DeletePerson(Position p, char surname) {

	Position np = p;

	if (p->next) {
		Position prev = NULL;
		while (np->next && strcmp(np->surname, surname) != 0) {
			prev = np;
			np = np->next;
		}
		if (prev && prev->next && strcmp(np->surname, surname) == 0) {
			printPerson(np);
			prev->next = np->next;
			free(np);
		}
	}
	else
		return PERSON_NOT_FOUND;


}
int menu(Position p) { //nesto ne valja sa funkcijon

	Position person;
	char c;
	printf("\nOdaberite zeljenu funkciju:\n");
	printf("F-Add to front.\n");
	printf("P-Print the list\n");
	printf("B-Add to back\n");
	printf("S-Find person by surname:\n");
	printf("D-Delete person from the list.\n");
	printf("E-Exit\n");
	scanf("%c", &c);

	switch (c) {
	case'F': {
		printf("Dodano na pocetak:\n");
		AddToFront(&p);
		break;
	}
	case'P': {
		printf("Lista:\n");
		PrintTheList(p->next);
		break;
	}
	case'B': {
		printf("Dodano na kraj:\n");
		AddToEnd(&p);
		break;
	}
	case'S': {
		char surname[MAX_LENGTH];
		printf("Unesite prezime za pretragu:\n");
		scanf("%s", surname);

		person = FindBySurname(p->next, surname);
		person ? printPerson(person) : printf("Can't find person\n");
		break;
	}
	case'D': {
		char surname[MAX_LENGTH];
		printf("Unesi prezime osobe za brisanje:\n");
		scanf("%s", surname);
		person = FindBySurname;
		if (person != NULL) {
			p = DeletePerson(&p, surname);
			printf("Osoba %s je obrisana iz liste.\n", surname);
		}
		else {
			printf("Osoba s prezimenom %s nije pronaðena.\n", surname);
		}
		break;

	}
	case'E':
		return 0;
	default:
		printf("Greska! Ponovo unesite funkciju koju zelite izvrsiti.\n");
		break;
	}
	return menu(p);

}