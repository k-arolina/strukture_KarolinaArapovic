<<<<<<< HEAD
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
	int brStud;
	//float rel_bod;
	//FILE* fp = NULL;
	brStud = readNoRowsInFile();
	if (brStud <= 0) {
		return 1;
	}



	allocMemAndReadStud(brStud);
	/*for (int i = 0; i < brStud; i++) {
		printf("%s %s %d ", st[i].ime, st[i].prezime, st[i].bodovi);

		st[i].relativni_broj_bodova = ((float)st[i].bodovi / max_bodovi )* 100;
		printf("%.2f%%\n", st[i].relativni_broj_bodova);
		printf("\n");
	}*/



	return 0;
}


int readNoRowsInFile() {

	int counter = 0;

	char buffer[MAX_SIZE] = { 0 };

	FILE* dat = fopen("studenti.txt", "r");


	if (!dat) {
		printf("neuspjesno otvorena!");
		return FILE_NOT_OPEN;

	}
	else




		while (!feof(dat))
		{
			fgets(buffer, MAX_SIZE, dat);
			counter++;
		}
	fclose(dat);

	return counter;
}
int allocMemAndReadStud(int noStud) {

	int i;


	Student* stud = (Student*)malloc(noStud * sizeof(Student));

	FILE* dat = fopen("studenti.txt", "r");




	if (!dat) {
		printf("neuspjesno otvorena!");

		return FILE_NOT_OPEN;

	}







	for (i = 0; i < noStud; i++) {
		fscanf(dat, " %s ", stud[i].ime);
		fscanf(dat, " %s  ", stud[i].prezime);
		fscanf(dat, " %d", &stud[i].bodovi);


	}

	printf("IME: Prezime: APS.Bodovi\n");
	for (i = 0; i < noStud; i++) {
		printf(" %s\t%s\t%d\n", stud[i].ime, stud[i].prezime, stud[i].bodovi);
		// printf(" %s\t",stud[i].ime);
		// printf(" %s\t",stud[i].prezime);
		// printf("%d\n",stud[i].bodovi);
		stud[i].relativni_broj_bodova = (float)stud[i].bodovi / 25 * 100;
		printf(" %.2f%%\n", stud[i].relativni_broj_bodova);
	}

	fclose(dat);

	free(stud);


	return 0;
=======
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
	int brStud;
	//float rel_bod;
	//FILE* fp = NULL;
	brStud = readNoRowsInFile();
	if (brStud <= 0) {
		return 1;
	}



	allocMemAndReadStud(brStud);
	/*for (int i = 0; i < brStud; i++) {
		printf("%s %s %d ", st[i].ime, st[i].prezime, st[i].bodovi);

		st[i].relativni_broj_bodova = ((float)st[i].bodovi / max_bodovi )* 100;
		printf("%.2f%%\n", st[i].relativni_broj_bodova);
		printf("\n");
	}*/



	return 0;
}


int readNoRowsInFile() {

	int counter = 0;

	char buffer[MAX_SIZE] = { 0 };

	FILE* dat = fopen("studenti.txt", "r");


	if (!dat) {
		printf("neuspjesno otvorena!");
		return FILE_NOT_OPEN;

	}
	else




		while (!feof(dat))
		{
			fgets(buffer, MAX_SIZE, dat);
			counter++;
		}
	fclose(dat);

	return counter;
}
int allocMemAndReadStud(int noStud) {

	int i;


	Student* stud = (Student*)malloc(noStud * sizeof(Student));

	FILE* dat = fopen("studenti.txt", "r");




	if (!dat) {
		printf("neuspjesno otvorena!");

		return FILE_NOT_OPEN;

	}







	for (i = 0; i < noStud; i++) {
		fscanf(dat, " %s ", stud[i].ime);
		fscanf(dat, " %s  ", stud[i].prezime);
		fscanf(dat, " %d", &stud[i].bodovi);


	}

	printf("IME: Prezime: APS.Bodovi\n");
	for (i = 0; i < noStud; i++) {
		printf(" %s\t%s\t%d\n", stud[i].ime, stud[i].prezime, stud[i].bodovi);
		// printf(" %s\t",stud[i].ime);
		// printf(" %s\t",stud[i].prezime);
		// printf("%d\n",stud[i].bodovi);
		stud[i].relativni_broj_bodova = (float)stud[i].bodovi / 25 * 100;
		printf(" %.2f%%\n", stud[i].relativni_broj_bodova);
	}

	fclose(dat);

	free(stud);


	return 0;
>>>>>>> 5c05faed82b84068df544e3205f9ae7f4b899640
}