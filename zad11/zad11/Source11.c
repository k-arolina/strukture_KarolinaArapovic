/* 11. Prepraviti zadatak 10 na nacin da se formira hash tablica drzava.Tablica ima 11 mjesta, a
funkcija za preslikavanje kljuc racuna da se zbraja ASCII vrijednost prvih pet slova drzave zatim
racuna ostatak cjelobrojnog dijeljenja te vrijednosti s velicinom tablice.Drzave s istim kljucem se
pohranjuju u vezanu listu sortiranu po nazivu drzave.Svaki cvor vezane liste sadrzi stablo
gradova sortirano po broju stanovnika, zatim po nazivu grada. */


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define MAX_LENGTH 50
#define FILE_OPENED_UNSECCESSFUL -1
#define MAX_LINE 1024
#define FAILED_MEMORY_ALLOCATION NULL
#define HASH_TABLE_SIZE 11


struct City;
typedef struct City* CityPosition;
typedef struct City {

	char name[MAX_LENGTH];
	int population;
	CityPosition next;
	CityPosition right;
	CityPosition left;

} city;

struct Country;
typedef struct Country* CountryPosition;
typedef struct Country {
	char name[MAX_LENGTH];
	CountryPosition next;
	CountryPosition right;
	CountryPosition left;
	CityPosition cityRootTree;
	city cityHead;

} _Country;

struct _hash_table;
typedef struct _hash_table HashTable;
struct _hash_table {
	CountryPosition buckets[HASH_TABLE_SIZE];
};

CountryPosition ReadFileOfCountries(CountryPosition country_head, CountryPosition country_root);
int createNewCountryFromBuffer(char* countryName, char* countryFile, CountryPosition* countries);
CountryPosition CreateNewCountryNode(char* countryName);
int insertSortedCountryList(CountryPosition headCountry, CountryPosition newCountry);
CityPosition createNewCityNode(char cityname[], int city_population);
CityPosition insertCityTree(CityPosition cityroot, CityPosition newCity);
int insertSortedCityList(CityPosition headCity, CityPosition newcity);
int printCountryList(CountryPosition headCountry);
int printCityTree(CityPosition root);
CountryPosition insertNewCountryTree(CountryPosition countryRootTree, CountryPosition newCountry);
int printCountryTree(CountryPosition countryRootTree);
int printCityList(CityPosition cityHeadList);
int findCountries(CountryPosition countryHeadList, CountryPosition countryRootTree, CountryPosition* countries);
CountryPosition searchCountryTree(CountryPosition countryRootTree, char* countryName);

HashTable* createHashTable();
unsigned int calculateHash(char* countryName);
void insertCountryIntoHashTable(HashTable* hashTable, CountryPosition newCountry);
CountryPosition searchCountryInHashTable(HashTable* hashTable, char* countryName);
int printAllCountriesFromHash(HashTable* hashTable);


int main()
{
	_Country head = { .name = {0},.next = NULL,.left = NULL,.cityRootTree = NULL,.cityHead = {.name = {0},
					.population = 0,.next = NULL, .left = NULL, .right = NULL} };

	CountryPosition CountryRootTree = NULL;
	CountryPosition CountryCurrentList = NULL;
	CountryPosition CountryCurrentTree = NULL;
	CountryPosition countries[] = { NULL,NULL };

	CountryRootTree = ReadFileOfCountries(&head, CountryRootTree);

	printCountryList(&head);
	printf("\n\n");

	printCountryTree(CountryRootTree);
	findCountries(&head, CountryRootTree, countries);

	CountryCurrentList = countries[0];
	CountryCurrentTree = countries[1];

	printf("\nCountry list: %s", CountryCurrentList->name);
	printf("\nCountry tree: %s", CountryCurrentTree->name);

	return 0;
}


//cita datoteku
CountryPosition ReadFileOfCountries(CountryPosition country_head, CountryPosition country_root) {

	char countryName[MAX_LINE] = { 0 };
	char countryFile[MAX_LINE] = { 0 };
	char nullString[MAX_LINE] = { 0 };
	CountryPosition newCountryList = NULL;
	CountryPosition newCountryTree = NULL;
	CountryPosition countries[] = { NULL, NULL };

	FILE* fptr = NULL;
	fptr = fopen("drzave.txt", "r");


	if (!fptr)
	{
		printf("File can not be opened!\n");
		return FILE_OPENED_UNSECCESSFUL;
	}
	else
		printf("test.txt file open successful\n");

	while (!feof(fptr))
	{
		fscanf(fptr, "%s %s", countryName, countryFile);

		//printf("%s %s\n", countryName, countryFile);		// works

		createNewCountryFromBuffer(countryName, countryFile, countries);
		newCountryList = countries[0];
		newCountryTree = countries[1];
		insertSortedCountryList(country_head, newCountryList);
		country_root = insertNewCountryTree(country_root, newCountryTree);
		strcpy(countryName, nullString);
		strcpy(countryFile, nullString);
	}

	fclose(fptr);

	return country_root;
}

int createNewCountryFromBuffer(char* countryName, char* countryFile, CountryPosition* countries)
{
	char countryLocation[MAX_LENGTH] = { 0 };
	FILE* countryfptr = NULL;
	CountryPosition newCountryList = NULL;
	CountryPosition newCountryTree = NULL;
	CityPosition newCityList = NULL;
	CityPosition newCity = NULL;
	char CityName[MAX_LENGTH] = { 0 };
	int CityPopulation = 0;

	strcpy(countryLocation, countryFile);		// gets the name of the country txt file

	countryfptr = fopen(countryFile, "r");

	if (!countryfptr)
	{
		printf("Can not open file!\n");
		return FILE_OPENED_UNSECCESSFUL;
	}
	else
		printf("%s file open successful\n", countryLocation);

	newCountryList = CreateNewCountryNode(countryName);
	newCountryTree = CreateNewCountryNode(countryName);

	while (!feof(countryfptr)) {
		fscanf(countryfptr, " %s %d", CityName, &CityPopulation);
		newCityList = createNewCityNode(CityName, CityPopulation);
		newCity = createNewCityNode(CityName, CityPopulation);
		insertSortedCityList(&newCountryTree->cityHead, newCityList);
		newCountryList->cityRootTree = insertCityTree(newCountryList->cityRootTree, newCity);
		newCityList = NULL;
	}
	countries[0] = newCountryList;
	countries[1] = newCountryTree;

	fclose(countryfptr);

	return EXIT_SUCCESS;
}

//funkcija za stvaranje novog cvora za drzavu
CountryPosition CreateNewCountryNode(char* countryName)
{
	CountryPosition newcountry = NULL;
	newcountry = (CountryPosition)malloc(sizeof(_Country));

	if (!newcountry) {
		printf("Can't allocate memory!");
		return FAILED_MEMORY_ALLOCATION;
	}

	strcpy(newcountry->name, countryName);
	newcountry->next = NULL;
	newcountry->left = NULL;
	newcountry->right = NULL;
	newcountry->cityRootTree = NULL;
	newcountry->cityHead.population = 0;
	newcountry->cityHead.next = NULL;
	newcountry->cityHead.left = NULL;
	newcountry->cityHead.right = NULL;

	return newcountry;
}
int insertSortedCountryList(CountryPosition headCountry, CountryPosition newCountry) {

	CountryPosition currentCountry = headCountry;

	while (currentCountry->next != NULL && strcmp(currentCountry->next->name, newCountry->name) < 0) {
		currentCountry = currentCountry->next;
	}

	newCountry->next = currentCountry->next;
	currentCountry->next = newCountry;


	return EXIT_SUCCESS;
}
CountryPosition insertNewCountryTree(CountryPosition countryRootTree, CountryPosition newCountry) {
	if (countryRootTree == NULL)
		return newCountry;
	if (strcmp(countryRootTree->name, newCountry->name) > 0)
		countryRootTree->left = insertNewCountryTree(countryRootTree->left, newCountry);
	else if (strcmp(countryRootTree->name, newCountry->name) <= 0)
		countryRootTree->right = insertNewCountryTree(countryRootTree->right, newCountry);
	return countryRootTree;
}



//funkcija z astvaranje novog cvora za grad
CityPosition createNewCityNode(char cityname[], int city_population) {
	CityPosition newcity = NULL;
	newcity = (CityPosition)malloc(sizeof(city));

	if (!newcity) {
		printf("Can't allocate memory!");
		return FAILED_MEMORY_ALLOCATION;
	}
	strcpy(newcity->name, cityname);
	newcity->population = city_population;
	newcity->next = NULL;
	newcity->left = NULL;
	newcity->right = NULL;

	return newcity;

}
//funkcija za dodavanje grada u stablo gradova
CityPosition insertCityTree(CityPosition cityroot, CityPosition newCity) {
	if (cityroot == NULL) {
		return newCity;
	}
	if (newCity->population < cityroot->population && strcmp(newCity->name, cityroot->name) > 0) {
		cityroot->left = insertCityTree(cityroot->left, newCity);
	}
	else if (newCity->population <= cityroot->population && strcmp(newCity->name, cityroot->name) > 0) {
		cityroot->right = insertCityTree(cityroot->right, newCity);

	}
	return cityroot;
}
int insertSortedCityList(CityPosition headCity, CityPosition newcity) {
	CityPosition currentCity = headCity;

	while (currentCity->next != NULL && currentCity->next->population > newcity->population) {
		currentCity = currentCity->next;
	}
	newcity->next = currentCity->next;
	currentCity->next = newcity;

	return EXIT_SUCCESS;
}

//ispis vezane liste drzave
int printCountryList(CountryPosition headCountry) {
	CountryPosition currentCountry = headCountry->next;
	while (currentCountry != NULL) {
		printf("\n%s", currentCountry->name);
		printCityTree(currentCountry->cityRootTree);
		currentCountry = currentCountry->next;
	}
	return EXIT_SUCCESS;
}
//inorder ispis stabla gradova
int printCityTree(CityPosition root) {
	if (root) {
		printCityTree(root->left);
		printf("\n\t%s %d", root->name, root->population);
		printCityTree(root->right);
	}
	return EXIT_SUCCESS;
}
int printCountryTree(CountryPosition countryRootTree) {
	if (countryRootTree) {
		printCountryTree(countryRootTree->left);
		printf("\n%s", countryRootTree->name);
		printCityList(&countryRootTree->cityHead);
		printCountryTree(countryRootTree->right);
	}
	return EXIT_SUCCESS;
}
int printCityList(CityPosition cityHeadList) {
	CityPosition currentCity = cityHeadList->next;
	while (currentCity != NULL) {
		printf("\n\t%s %d", currentCity->name, currentCity->population);
		currentCity = currentCity->next;
	}
}
int findCountries(CountryPosition countryHeadList, CountryPosition countryRootTree, CountryPosition* countries) {
	CountryPosition countryCurrentList = countryHeadList->next;
	CountryPosition countryCurrentTree = countryRootTree;
	char countryName[MAX_LENGTH] = { 0 };
	printf("\n\nEnter country name: ");
	scanf(" %s", countryName);

	while (countryCurrentList != NULL && strcmp(countryCurrentList->name, countryName)) {
		countryCurrentList = countryCurrentList->next;
	}

	countryCurrentTree = searchCountryTree(countryRootTree, countryName);

	countries[0] = countryCurrentList;
	countries[1] = countryCurrentTree;

	return EXIT_SUCCESS;
}
CountryPosition searchCountryTree(CountryPosition countryRootTree, char* countryName) {
	if (countryRootTree == NULL || strcmp(countryRootTree->name, countryName) == 0)
		return countryRootTree;

	if (strcmp(countryRootTree->name, countryName) > 0)
		return searchCountryTree(countryRootTree->left, countryName);

	return searchCountryTree(countryRootTree->right, countryName);
}


HashTable* createHashTable()
{
	HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
	if (!hashTable)
	{
		printf("Hash table memory allocation unsuccessful\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < HASH_TABLE_SIZE; i++)
		hashTable->buckets[i] = NULL;

	return hashTable;
}

unsigned int calculateHash(char* countryName)
{
	unsigned int value = 0;
	int i = 0;
	while (i < 5 && countryName[i] != '\0')
	{
		value += (unsigned int)countryName[i];
		i++;
	}

	return value % HASH_TABLE_SIZE;
}


void insertCountryIntoHashTable(HashTable* hashTable, CountryPosition newCountry)
{
	unsigned int index = calculateHash(newCountry->name);

	if (hashTable->buckets[index] == NULL)
	{
		hashTable->buckets[index] = newCountry;
		newCountry->next = NULL;
	}

	else
	{
		newCountry->next = hashTable->buckets[index];
		hashTable->buckets[index] = newCountry;
	}
}

CountryPosition searchCountryInHashTable(HashTable* hashTable, char* countryName)
{
	unsigned int index = calculateHash(countryName);
	CountryPosition currentCountry = hashTable->buckets[index];

	while (currentCountry != NULL && strcmp(currentCountry->name, countryName) != 0)
		currentCountry = currentCountry->next;

	return currentCountry;
}

int printAllCountriesFromHash(HashTable* hashTable)
{
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		CountryPosition currentCountry = NULL;
		currentCountry = hashTable->buckets[i];

		while (currentCountry != NULL)
		{
			printf("%s\n", currentCountry->name);
			printCityTree(currentCountry->cityRootTree);
			currentCountry = currentCountry->next;
		}
	}
}