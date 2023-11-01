#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LENGTH 1024
#define PERSON_NOT_FOUND -1
#define FILE_NOT_OPEN -3
#define ALLOC_FAIL -2


/*2. Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
A. dinamièki dodaje novi element na poèetak liste,
B. ispisuje listu,
C. dinamièki dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable*/

/* 3. Prethodnom zadatku dodati funkcije:
A. dinamicki dodaje novi element iza odredjenog elementa,
B. dinamicki dodaje novi element ispred odredjenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. cita listu iz datoteke. */



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
Position FindBySurname(Position p);
int DeletePerson(Position p);
int menu(Position p);
int printPerson(Position p);
int AddInFrontOfPerson(Position p);
int AddBehindPerson(Position p);
Position FindPrevious(Position p);
int ReadListFromTheFile(Position p);
int AddListInFile(Position p);
int SortBySurname(Position p);
Position Search(Position p, char surnamep[MAX_LENGTH]);
int countElements(Position p);


int main()
{
	Person Head = { .name = 0, .surname = 0, .birth_year = 0, .next = NULL };

	menu(&Head);

	return 0;

}
Position createPerson() {
	Position New_Person = NULL;
	char ime[MAX_LENGTH] = { 0 };
	char prezime[MAX_LENGTH] = { 0 };
	int god_rod = 0;

	New_Person = (Position)malloc(sizeof(Person));
	if (!New_Person) {
		printf("Memory not allocated!\n"); //provjeraje je li pravilno alocirano!
		return NULL;
	}
	printf("Unesi ime:\n");
	scanf("%s", ime);

	printf("Unesi prezime:\n");
	scanf("%s", prezime);

	printf("Unesi godinu rodenja:\n");
	scanf(" %d", &New_Person->birth_year);

	strcpy(New_Person->name, ime);
	strcpy(New_Person->surname, prezime);


	return New_Person; //moramo vracat pointer!! PAZI!!!
}

int AddToFront(Position p) {
	Position np = NULL;
	np = createPerson();//stvara novu osobu koju cemo upisat u listu


	np->next = p->next;
	p->next = np;

	return 0;
}
int PrintTheList(Position p) {
	while (p != NULL) {   /*printa dok p ne pokazuje na NULL(kad dode
						  do NULL znaci da je to kraj liste*/
		printf("\nPerson:\n");
		printf("\tName: %s\n", p->name);
		printf("\tSurname: %s\n", p->surname);
		printf("\tName: %d\n", p->birth_year);

		p = p->next;
	}
	return 0;
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
int printPerson(Position p) {  //obicna funkcija koja printa

	printf("\n--------\n");
	printf("%s", p->name);
	printf("\t");
	printf("%s", p->surname);
	printf(" %d", p->birth_year);


	return 0;

}
int AddToEnd(Position p) {
	Position np = NULL;
	np = createPerson();

	while (p->next != NULL) {/*Stavljamo p->next jer nan treba 
							 prvi iduci element iz liste i trazimo po listi
							 zadnji element*/
		p = p->next;
	}
	np->next = p->next;//isto kao i kod funkc AddToFront
	p->next = np;

	return 0;
}

Position FindBySurname(Position p) {
	Position Np = p;
	char prezime[MAX_LENGTH] = { 0 };

	
	if (!p) {						//provjeraje je li lista ima elemenata
		printf("Empty list\n");
		return NULL;
	}
	printf("Enter surname:\n");
	scanf("%s", prezime);

	while (Np != NULL) { 
		if (strcmp(Np->surname, prezime) == 0) {
			return Np;
		}
		else {
			Np = Np->next;
		}

	}
	return NULL;//vraca pointer!!!

}
int DeletePerson(Position p) {

	Position np = p;
	char surnametemp[MAX_LENGTH] = { 0 };
	printf("Enter surname:\n");
	scanf("%s", surnametemp);

	if (p->next) {			//iteriramo po listi
		Position prev = NULL;
		while (np->next && strcmp(np->surname, surnametemp) != 0) {/*itreiramo i postavljamo
																   np i prev*/
			prev = np;
			np = np->next;
		}
		if (prev && prev->next && strcmp(np->surname, surnametemp) == 0) { //ovde se dogada brisanje
			printPerson(np);
			prev->next = np->next;
			free(np);
		}
	}
	else
		return PERSON_NOT_FOUND;


}
int menu(Position p) { 

	Position person;
	int c;
	printf("\nChoose an option\n");
	printf("\n----------------\n");
	printf("1-Add to front\n");
	printf("2-Print the list\n");
	printf("3-Add to back\n");
	printf("4-Find person by surname\n");
	printf("5-Delete person from the list\n");
	printf("6-Add in front of person\n");
	printf("7-Add after person\n ");
	printf("8-Sort by surname\n");
	printf("9-Add list in file\n");
	printf("10-Read the file\n");
	printf("11-Exit\n");

	printf("\n----------------\n");
	scanf("%d", &c);

	switch (c) {
	case 1:
		printf("Dodano na pocetak:\n");
		AddToFront(p);
		break;

	case 2:
		printf("Lista:\n");
		PrintTheList(p->next);
		break;

	case 3:
		printf("Dodano na kraj:\n");
		AddToEnd(p->next);
		break;

	case 4:

		printf("Find by surname:\n");
		person = FindBySurname(p->next);
		person ? printPerson(person) : printf("Can't find person\n");
		break;

	case 5:
	
		printf("Delete person:\n");

	/*	if (person != NULL) {
			p = DeletePerson(&p);
			printf("Osoba je obrisana iz liste.\n");
		}
		else {
			printf("Osoba nije pronaðena.\n");
		}*/
		DeletePerson(p);
		break;
	case 6:
		printf("Add in front of person\n");
		AddInFrontOfPerson(p);
		break;
	case 7:
		printf("Add after person\n ");
		AddBehindPerson(p);
		break;
	case 8:
		printf("Sort by surname\n");
		SortBySurname(p);
		break;
	case 9:
		printf("Add list in file\n");
		AddListInFile(p);
		break;
	case 10:

		printf("Read the file\n");
		ReadListFromTheFile(p);
		break;

	case 11:
		printf("Exit.\n");
		return 0;
		break;
	default:
		printf("Error!Enter your choice again:\n");
		break;
	}
	return menu(p);

}
Position FindPrevious(Position p) {

	Position prev = p;
	char surn[MAX_LENGTH] = { 0 };
	
	printf("\nEnter surname you are serching:\n");
	scanf("%s", surn);

	while (p != NULL && strcmp(p->surname, surn) != 0) { /*Trazimo element dok ga se
														 ne nade ili ne dode do kraja liste*/
		prev = p;
		p = p->next;
	}
	if (p != NULL && strcmp(p->surname, surn) == 0) {/*ako je pronaden cvor s
													 prezimenom vraca prethpdni cvor*/
		return prev;
	}

	return NULL;//ako nije pronaden vraca NULL

	
}

int AddInFrontOfPerson(Position p) {
	Position np;
	
	
	p= FindPrevious(p);//sa p->next ne radi za ubacivanje ispirid prvog elementa
	if (!p) {
		printf("Empty list!\n");
		return PERSON_NOT_FOUND;
	
	}
	if (p!= NULL) {
		np = createPerson();
		np->next = p->next;
		p->next = np;
	}

	return 0;
}

Position Search(Position p, char surnamep[MAX_LENGTH]) {


	while (p != NULL) {
		if (strcmp(p->surname, surnamep) == 0) {
			return p;
		}
		else {
			p = p->next;
		}

	}
	return NULL;
}



int AddBehindPerson(Position p) {
	Position np;
	char surn[MAX_LENGTH] = { 0 };

	printf("Enter surname:\n");
	scanf("%s", surn);
	
	p = Search(p->next,surn);

	if(p!= NULL) {
		np = createPerson();
		np->next = p->next;
		p->next = np;
	}
	return 0;
}


int SortBySurname(Position p) {
	Position j, prev_j, temp, end;
	end = NULL;

	while (p->next != end)
	{
		prev_j = p;
		j = p->next;
		while (j->next != end)
		{
			if (strcmp(j->surname,j->next->surname) >0)	
			{
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}

			prev_j = j;
			j = j->next;
		}

		end = j;
	}

	return 0;
}
int countElements(Position p) {
	int count = 0;
	while (p != NULL) {
		count++;
		p = p->next;
	}
	return count;
}

int AddListInFile(Position p) {
	int i, NoStud;
	FILE* filePointer = NULL;

	NoStud = countElements(p);

	

	filePointer = fopen("Studenti.txt", "w");


	if (!filePointer)
	{
		printf("Unsuccessful file open in function allocMemAndReadStud\n");

		return FILE_NOT_OPEN;
	}
	fprintf(filePointer, "NAME:\tSURNAME:\tBIRTHYEAR:\t\n");
	while (p != NULL) {
		for (i = 0; i < NoStud; i++) {
			fprintf(filePointer, "%s\t %s\t %d\t\n", p->name, p->surname, p->birth_year);
			p = p->next;
		}
	}
	fclose(filePointer);
	return 0;
}
int ReadListFromTheFile(Position p) {
	int counter = 0;
	int i;
	int NoStud = 0;
	FILE* filePointer = NULL;
	char buffer[MAX_LENGTH] = { 0 };
	filePointer = fopen("Studenti.txt", "r");

	if (!filePointer)
	{
		printf("Unsuccessful file open in function allocMemAndReadStud\n");

		return FILE_NOT_OPEN;
	}
	while (!feof(filePointer))
	{
		fgets(buffer, MAX_LENGTH, filePointer);
		counter++;
	}
	NoStud = counter;

	for (i = 0; i < NoStud; i++)		// ucitavanje podataka u strukturu stud
	{
		fscanf(filePointer, " %s ", p->name);
		fscanf(filePointer, " %s  ", p->surname);
		fscanf(filePointer, " %d", p->birth_year);
	}
	printf("\nNAME:\tSURNAME:\tBIRTHYEAR:\t\n");
	while (p != NULL) {
		for (i = 0; i < NoStud; i++)//isprinta listu,ali na kraju program izlazi sa trash vrijednosti
		{
			printf("%s\t", p->name);
			printf("%s\t", p->surname);
			printf("%d\t", p->birth_year);
			printf("\n");
			p = p->next;
		}
	
	}
	fclose(filePointer);


	return 0;
}
