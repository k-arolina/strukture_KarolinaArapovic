#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 50

/* 7. Napisati program koji pomocu vezanih listi(stabala) predstavlja strukturu direktorija.
Omoguciti unos novih direktorija i pod - direktorija, ispis sadrzaja direktorija i
povratak u prethodni direktorij.Tocnije program treba preko menija simulirati
koristenje DOS naredbi : 1 - "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz. */

struct _directory;
typedef struct _directory* PositionDirectory;
typedef struct _directory {
	char name[MAX_NAME_LENGTH];
	PositionDirectory firstSubDirectory;	// first child
	PositionDirectory nextSubDirectory;		// next sibling
} Directory;

int menu(PositionDirectory currentDirectory);
PositionDirectory CreatenewDirectory(char name[MAX_NAME_LENGTH]);
PositionDirectory newSubdirectory(char name[MAX_NAME_LENGTH], PositionDirectory currentDirectory);
PositionDirectory changeDirectory(char name[MAX_NAME_LENGTH], PositionDirectory currentDirectory);
PositionDirectory GoToPrevious_Directory(PositionDirectory currentDirectory);
int PrintDirectory(PositionDirectory currentDirectory);
int main()
{
	Directory headDirectory = { .name = {0}, .firstSubDirectory = NULL, .nextSubDirectory = NULL };	// head

	PositionDirectory rootDirectory = CreatenewDirectory("C:",NULL);	// root
	headDirectory.firstSubDirectory = rootDirectory;		// set it as heads first child

	PositionDirectory currentDirectory = rootDirectory;		// points to root

	menu(currentDirectory);

	return 0;
}

int menu(PositionDirectory currentDirectory)
{
	int choice;
	char dirName[MAX_NAME_LENGTH] = { 0 };

	printf("\nChoose an option:\n");
	printf("-----------------------\n");
	printf("1 - create new sub directory -md\n");
	printf("2 - change directory -cd dir\n");
	printf("3 - return to previous directory -cd...\n");
	printf("4 - print directory contents -dir\n");
	printf("5 - exit\n");
	printf("-----------------------\n");
	scanf("%d", &choice);
	printf("\n");

	switch (choice)
	{
	case 1:		// create new
		printf("\ncreate new sub directory -md:\n");
		printf("Enter sub directory name: ");
		scanf("%s", dirName);
		newSubdirectory(dirName, currentDirectory);
		break;

	case 2:		// change dir 
		printf("\nchange directory -cd dir:\n");		// move to any directory
		printf("Enter directory name: ");
		scanf("%s", dirName);
		currentDirectory = changeDirectory(dirName, currentDirectory);		// current now points to the one with dirName
		break;

	case 3:		// return to prev ND
		printf("\nreturn to previous directory -cd...:\n");
		currentDirectory = GoToPrevious_Directory(currentDirectory);
		break;

	case 4:		// print content ND
		printf("\nprint directory contents -dir:\n");
		PrintDirectory(currentDirectory);
		break;

	case 5:		// exit
		printf("\nExit\n");
		return 0;
		break;

	default:
		printf("\nError! Enter your choice again:\n");
		break;
	}

	return menu(currentDirectory);
}

PositionDirectory CreatenewDirectory(char name[MAX_NAME_LENGTH])
{
	PositionDirectory newDirectory = NULL;
	newDirectory = (PositionDirectory)malloc(sizeof(Directory));

	if (!newDirectory) {
		printf("Can't create directory\n");
		return NULL;
	}
	strcpy(newDirectory->name, name);
	newDirectory->firstSubDirectory = NULL;
	newDirectory->nextSubDirectory = NULL;

	return newDirectory;
}

PositionDirectory newSubdirectory(char name[MAX_NAME_LENGTH], PositionDirectory currentDirectory)
// adds new subdirectory in front of the other ones // like add to front in lists
{
	PositionDirectory newSubDirectory = NULL;
	newSubDirectory =  CreatenewDirectory(name);

	newSubDirectory->nextSubDirectory = currentDirectory->firstSubDirectory;
	currentDirectory->firstSubDirectory = newSubDirectory;

	return newSubDirectory;
}

PositionDirectory changeDirectory(char name[MAX_NAME_LENGTH], PositionDirectory currentDirectory)
{
	if (currentDirectory == NULL)
		return NULL;

	PositionDirectory temp = currentDirectory->nextSubDirectory;
	while (temp != NULL)
	{
		if (strcmp(temp->name, name) == 0) {
			return temp;
		}
		temp = temp->nextSubDirectory;
	}
	

	printf("Directory %s not found\n",name);
	return currentDirectory;
}
PositionDirectory GoToPrevious_Directory(PositionDirectory currentDirectory) {
	{
		if (currentDirectory == NULL) {
			printf("Error: No current directory.\n");
			return NULL;


		}
		if (currentDirectory->firstSubDirectory == NULL) {
			printf("Error:already at the root directory.\n");
			return currentDirectory;
		}
		return currentDirectory->firstSubDirectory;
	}
}
int PrintDirectory(PositionDirectory currentDirectory) {
	if (currentDirectory == NULL) {
		printf("Error! No current direcotry.\n");
		return -1;
	}
	printf("Directory %s content:\n", currentDirectory->name);
	PositionDirectory temp = currentDirectory->nextSubDirectory;
	while (temp != NULL) {
		printf("- %s\n", temp->name);
		temp = temp->nextSubDirectory;
	}
	return 0;
}