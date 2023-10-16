#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 128
#define FILE_NOT_OPEN -1
#define ALLOC_FAIL -2

typedef struct _student
{
	char name[MAX_SIZE];

} student;

int allocMemAndReadStud(int noStud)
{
	int counter = 0;
	FILE* dat = NULL;
	student* students = NULL;

	return 0; //?????
}

int readNoRowsInFile()
{
	int counter = 0;
	FILE* dat = NULL;
	char buffer[MAX_SIZE] = { 0 };

	dat = fopen("studenti.txt", "r");

	if (!dat)
	{
		printf("neuspjesno otvaranje\n");

		return FILE_NOT_OPEN;
	}

	while (!feof(dat))
	{
		fgets(buffer, MAX_SIZE, dat);
		counter++;
	}

	fclose(dat);

	return counter;
};

int main()
{
	student* stud = NULL;
	int noStud = 0;

	noStud = readNoRowsInFile();

	stud = (student*)malloc(sizeof(student)*noStud);

	if (!stud)
	{
		printf("neuspjesna alokacija\n");

		return ALLOC_FAIL;
	}
}