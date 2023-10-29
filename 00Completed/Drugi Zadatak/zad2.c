#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct person Person;
typedef struct person* Position;

struct person {
	char name[20];
	char surname[20];
	int birth_year;
	Position next;

};
Position createPerson();
int AddToFront(Position p);
int PrintTheList(Position p);
int AddToEnd(Position p);
int Find(Position p);
int DeleteEl(Position p);


int main()
{
	Person Head;
	Head.next = NULL;

	AddToFront(&Head);

	AddToFront(&Head);

	AddToFront(&Head);

	PrintTheList(Head.next);
	/*AddToEnd(&Head);
	PrintTheList(Head.next);*/

	return 0;

}
Position createPerson() {
	Position New_Person = NULL;
	char ime[50] = { 0 };
	char prezime[50] = { 0 };
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

	if (np) {
		np->next = p->next;
		p->next = np;
	}
	return 0;
}
int PrintTheList(Position p) {

	while (p != NULL) {
		printf("%s ", p->name);
		printf("%s ", p->surname);
		printf("%d", p->birth_year);
		p = p->next;
	}
	return 0;

}
//int AddToEnd(Position p) {
//
//	Position np = NULL;
//	np = createPerson();
//
//
//	if (np) {
//		np->next = p->next;
//		p->next = np;
//	}
//
//	return np;
//}