/* 7. Napisati program koji pomocu vezanih listi(stabala) predstavlja strukturu direktorija.
Omoguciti unos novih direktorija i pod - direktorija, ispis sadrzaja direktorija i
povratak u prethodni direktorij.Tocnije program treba preko menija simulirati
koristenje DOS naredbi : 1 - "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz. */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 50

struct _directory;
typedef struct _directory* PositionDirectory;
typedef struct _directory {
	char name[MAX_NAME_LENGTH];
	PositionDirectory firstSubDirectory;	// first child
	PositionDirectory nextDirectory;		// next sibling
} Directory;

struct _level;
typedef struct _level* PositionLevel;
typedef struct _level {
	PositionDirectory directoryLevel;		// adress of a subdir on current level
	PositionLevel next;						// ptr to next stack element
} Level;


int menu(PositionDirectory currentDirectory, PositionLevel headLevel);
PositionDirectory newDirectory(char name[MAX_NAME_LENGTH]);
PositionDirectory newSubdirectory(char name[MAX_NAME_LENGTH], PositionDirectory currentDirectory);
PositionDirectory changeDirectory(char name[MAX_NAME_LENGTH], PositionDirectory currentDirectory);
int printContent(PositionDirectory currentDirectory);
int push(PositionLevel headLevel, PositionDirectory directoryLevel);
PositionDirectory pop(PositionLevel headLevel);
PositionLevel createNewLevel(PositionDirectory directoryLevel);

int main()
{
	Directory headDirectory = { .name = {0}, .firstSubDirectory = NULL, .nextDirectory = NULL };	// head

	PositionDirectory rootDirectory = newDirectory("C:");	// root
	headDirectory.firstSubDirectory = rootDirectory;		// set it as heads first child

	PositionDirectory currentDirectory = rootDirectory;		// points to root

	Level headLevel = { .directoryLevel = NULL, .next = NULL };
	push(&headLevel, currentDirectory);

	menu(currentDirectory, &headLevel);

	free(rootDirectory);

	return 0;
}

int menu(PositionDirectory currentDirectory, PositionLevel headLevel)
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
	scanf_s("%d", &choice);
	printf("\n");

	switch (choice)
	{
	case 1:		// create new sibling dir
		printf("\ncreate new sub directory -md:\n");
		printf("Enter sub directory name: ");
		scanf("%s", dirName);
		newSubdirectory(dirName, currentDirectory);
		break;

	case 2:		// change dir 
		printf("\nchange directory -cd dir:\n");		// move to any child directory
		printf("Enter directory name: ");
		scanf("%s", dirName);
		currentDirectory = changeDirectory(dirName, currentDirectory);		// current now points to the one with dirName
		push(headLevel, currentDirectory);	// moves down a level
		break;

	case 3:		// return to prev // go back a level
		printf("\nreturn to previous directory -cd...:\n");
		currentDirectory = pop(&headLevel);
		printf("Current directory: %s\n", currentDirectory->name);
		break;

	case 4:		// print content
		printf("\nprint directory contents -dir:\n");
		printContent(currentDirectory);
		break;

	case 5:		// exit
		printf("\nExit\n");
		return 0;
		break;

	default:
		printf("\nError! Enter your choice again:\n");
		break;
	}

	return menu(currentDirectory, headLevel);
}

PositionDirectory newDirectory(char name[MAX_NAME_LENGTH])
{
	// allocates memory for new PositionDirectory var

	PositionDirectory newDirectory = NULL;
	newDirectory = (PositionDirectory)malloc(sizeof(Directory));

	if (!newDirectory) {
		printf("Can't create directory\n");
		return NULL;
	}
	strcpy(newDirectory->name, name);
	newDirectory->firstSubDirectory = NULL;
	newDirectory->nextDirectory = NULL;

	return newDirectory;
}

PositionDirectory newSubdirectory(char name[MAX_NAME_LENGTH], PositionDirectory currentDirectory)
{
	// adds new sibling directory in front of the other ones // like add to front in lists

	PositionDirectory newSubDirectory = NULL;
	newSubDirectory = newDirectory(name);

	newSubDirectory->nextDirectory = currentDirectory->firstSubDirectory;
	currentDirectory->firstSubDirectory = newDirectory;

	return newDirectory;
}

PositionDirectory changeDirectory(char name[MAX_NAME_LENGTH], PositionDirectory currentDirectory)
{
	// only needs to search thru currents child dirs

	if (currentDirectory == NULL)
		return NULL;

	if (strcmp(currentDirectory->name, name) == 0)
		return currentDirectory;

	PositionDirectory currentDirectoryChild = currentDirectory->firstSubDirectory;

	while (currentDirectoryChild != NULL)
	{
		if (strcmp(currentDirectoryChild->name, name) == 0)
			return currentDirectoryChild;

		currentDirectoryChild = currentDirectoryChild->nextDirectory;
	}

	printf("Directory not found\n");
	return currentDirectory;
}

int printContent(PositionDirectory currentDirectory)
{
	printf("Directory %s: ", currentDirectory->name);
	printf("\n");

	PositionDirectory subdirectory = currentDirectory->firstSubDirectory;

	while (subdirectory != NULL) {
		printf("\t%s\n", subdirectory->name);
		subdirectory = subdirectory->nextDirectory;
	}
	if (currentDirectory->firstSubDirectory == NULL) {
		printf("\t(empty)\n");
	}
	return EXIT_SUCCESS;
}

/*PositionDirectory changeDirectory(char name[MAX_NAME_LENGTH], PositionDirectory currentDirectory)
// recursive search
{
	if (currentDirectory == NULL)
		return NULL;

	if (strcmp(currentDirectory->name, name) == 0)
		return currentDirectory;

	PositionDirectory currentDirectoryChild = changeDirectory(name, currentDirectory->firstSubDirectory);
	if (currentDirectoryChild != NULL)
		return currentDirectoryChild;

	//PositionDirectory currentDirectorySibling = changeDirectory(name, currentDirectory->nextSubDirectory);
	//if (currentDirectorySibling != NULL)
	//	return currentDirectorySibling;

	printf("Directory not found\n");
	return currentDirectory;
}*/

int push(PositionLevel headLevel, PositionDirectory directoryLevel)		// goes down a level
{
	PositionLevel newLevel = NULL;

	newLevel = createNewLevel(directoryLevel);
	if (!newLevel) {
		perror("Error in creating new level!\n");
		return NULL;
	}

	newLevel->next = headLevel->next;
	headLevel->next = newLevel;
}

PositionDirectory pop(PositionLevel headLevel)	// goes back a level
{
	PositionLevel toDelete = NULL;
	PositionDirectory directoryLevel = NULL;

	toDelete = headLevel->next;
	if (!toDelete) {
		printf("Stack is empty!\n");
		return NULL;
	}

	headLevel->next = toDelete->next;
	directoryLevel = toDelete->directoryLevel;
	free(toDelete);

	return directoryLevel;
}

PositionLevel createNewLevel(PositionDirectory directoryLevel)
{
	PositionLevel newLevel = NULL;

	newLevel = (PositionLevel)malloc(sizeof(Level));
	if (!newLevel) {
		perror("Can't allocate memory!\n");
		return NULL;
	}

	newLevel->directoryLevel = directoryLevel;
	newLevel->next = NULL;

	return newLevel;
}