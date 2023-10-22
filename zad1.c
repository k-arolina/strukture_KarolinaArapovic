#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 128
#define FILE_NOT_OPEN -1
#define ALLOC_FAIL -2
#define max_bodovi 25



/* 
Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/
typedef struct {
	char ime[50];
	char prezime[50];
	int bodovi;
	float relativni_broj_bodova;
}Student;

int readNoRowsInFile();
int allocMemAndReadStud(int noStud);


int main()
{
	int i;
	int brRed;

	brRed = readNoRowsInFile();
	allocMemAndReadStud(brRed);

	
	
	return 0;
}


int readNoRowsInFile() {
	int counter = 0;

	FILE* dat = NULL;
	char buffer[MAX_SIZE] = { 0 };
	
	dat = fopen("studenti.txt", "r");


	if (!dat)
	{
		printf("Neuspjesno otvaranje!\n");
		return FILE_NOT_OPEN;

	}

	while (!feof(dat))
	{
		fgets(buffer,MAX_SIZE, dat);
		counter++;
	}
	fclose(dat);

	return counter;
}
int allocMemAndReadStud(int noStud) {

	int i;
	
	
	Student* stud = (Student*)malloc(noStud * sizeof(Student));
	FILE* dat = NULL;
	dat = fopen("studenti.txt", "r");




	if (!dat) {
		printf("Nespjesno otvaranje!");
		
		return FILE_NOT_OPEN;
	}
	for (i = 0; i < noStud; i++) {
		fscanf(dat, "%s", stud->ime);
		fscanf(dat, " %s", stud->prezime);
		fscanf(dat, " %d", &stud->bodovi);
		

	}
	for (i = 0; i < noStud; i++) {


		stud->relativni_broj_bodova = stud->bodovi / max_bodovi * 100;
	}

	for (i = 0; i < noStud; i++) {
		printf("%s %s %d %f\n", stud->ime, stud->prezime, stud->bodovi, stud->relativni_broj_bodova);
	}
	fclose(dat);


	return 0;
}