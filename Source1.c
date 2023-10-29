/*  1. Napisati program koji prvo procita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamicki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i ucitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrzi ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100  */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define MAX_SIZE 128
#define FILE_NOT_OPEN -1
#define ALLOC_FAIL -2
#define MAX_PTS 50

typedef struct _student		// ime prezime i bodovi
{
	char name[MAX_SIZE];
	char lastn[MAX_SIZE];
	int pts;

} student;



int readNoRowsInFile();
int allocMemAndReadStud(int noStud);



int main()
{
	int noStud = 0;
	int i = 0;

	noStud = readNoRowsInFile();

	//printf("Number of students in file: %d\n", noStud);

	allocMemAndReadStud(noStud);

	return 0;
}



int readNoRowsInFile()
{
	int counter = 0;
	FILE* f = NULL;
	char buffer[MAX_SIZE] = { 0 };

	f = fopen("studenti.txt", "r");

	if (!f)
	{
		printf("Unsuccessful file open in function readNoRowsInFile\n");

		return FILE_NOT_OPEN;
	}

	while (!feof(f))
	{
		fgets(buffer, MAX_SIZE, f);
		counter++;
	}

	fclose(f);

	return counter;
};

int allocMemAndReadStud(int noStud)
{
	int i = 0;
	student* stud = (student*)malloc(noStud * sizeof(student));
	FILE* f = NULL;

	f = fopen("studenti.txt", "r");

	if (!f)
	{
		printf("Unsuccessful file open in function allocMemAndReadStud\n");

		return FILE_NOT_OPEN;
	}

	for (i = 0; i < noStud; i++)		// ucitavanje podataka u strukturu stud
	{
		fscanf(f, " %s ", stud[i].name);
		fscanf(f, " %s  ", stud[i].lastn);
		fscanf(f, " %d", &stud[i].pts);
	}

	printf("\nNAME\tLAST NAME\tPOINTS\tPERCENTAGE(50pts max)\n");
	for (i = 0; i < noStud; i++)
	{
		printf("%s\t", stud[i].name);
		printf("%8s\t", stud[i].lastn);
		printf("%5d\t", stud[i].pts);
		printf("%5f\n", (float)(stud[i].pts) / MAX_PTS * 100);
	}

	fclose(f);

	return 0;
}