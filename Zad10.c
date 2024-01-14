/*10. Napisati program koji �ita datoteku drzave.txt u kojoj su zapisani nazivi pojedinih dr�ava. Uz
ime dr�ave u datoteci se nalazi i ime dodatne datoteke u kojoj se nalaze gradovi pojedine
dr�ave. Svaka datoteka koja predstavlja dr�avu sadr�i popis gradova u formatu naziv_grada,
broj_stanovnika.
a) Potrebno je formirati sortiranu vezanu listu dr�ava po nazivu. Svaki �vor vezane liste
sadr�i stablo gradova sortirano po broju stanovnika, zatim po nazivu grada.
b) Potrebno je formirati stablo dr�ava sortirano po nazivu. Svaki �vor stabla sadr�i vezanu
listu gradova sortiranu po broju stanovnika, zatim po nazivu grada.
Nakon formiranja podataka potrebno je ispisati dr�ave i gradove te omogu�iti korisniku putem
tastature pretragu gradova odre�ene dr�ave koji imaju broj stanovnika ve�i od unosa na
tastaturi.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 50
#define FILE_OPENED_UNSECCESSFUL -1
#define MAX_LINE 1024
#define FAILED_MEMORY_ALLOCATION NULL

struct City;
typedef struct City* CityPosition;
typedef struct City {

	char name[MAX_LENGTH];
	int population;
	CityPosition next;
	CityPosition right;
	CityPosition left;

}city;

struct Country;
typedef struct Country* CountryPosition;
typedef struct Country {
	char name[MAX_LENGTH];
	CountryPosition next;
	CountryPosition right;
	CountryPosition left;
	CityPosition cityRootTree;
	city cityHead;

}_Country;

CountryPosition ReadFileOfCountries(CountryPosition country_head, CountryPosition country_root);
int createNewCountryFromBuffer(char* countryName, char* countryFile, CountryPosition* countries);
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
	CountryPosition countries[] = { NULL,NULL };

	FILE* fptr = fopen("drzave.txt", "r");


	if (!fptr) {
		printf("File can not be opened!\n");
		return FILE_OPENED_UNSECCESSFUL;
	}

	while (!feof(fptr)) {
		fscanf(fptr, " %s %s", countryName, countryFile);
		createNewCountryFromBuffer(countryName, countryFile, countries);
		newCountryList = countries[0];
		newCountryTree = countries[1];
		insertSortedCountryList(country_head, newCountryList);
		country_root= insertNewCountryTree(country_root, newCountryTree);
		strcpy(countryName, nullString);
		strcpy(countryFile, nullString);

		
	}
	fclose(fptr);
	return country_root;
}
int createNewCountryFromBuffer(char* countryName, char* countryFile, CountryPosition* countries) {
	char countryLocation[MAX_LENGTH] = { 0 };
	FILE* countryfptr = NULL;
	CountryPosition newCountryList = NULL;
	CountryPosition newCountryTree = NULL;
	CityPosition newCityList = NULL;
	CityPosition newCity = NULL;
	char CityName[MAX_LENGTH] = { 0 };
	int CityPopulation = 0;

	strcpy(countryLocation, countryFile);

	countryfptr = fopen(countryLocation, "r");
	if (!countryfptr) {
		printf("Can not open file!\n");
		return FILE_OPENED_UNSECCESSFUL;
	}

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
CountryPosition CreateNewCountryNode(char* countryName) {
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
	newcountry->cityHead.next= NULL;
	newcountry->cityHead.left = NULL;
	newcountry->cityHead.right = NULL;

	return newcountry;
}
int insertSortedCountryList(CountryPosition headCountry, CountryPosition newCountry) {
	
	CountryPosition currentCountry = headCountry;
	

	/*if (currentCountry == NULL || strcmp(currentCountry->name, newCountry->name) < 0) {
		newCountry->next = currentCountry;
		return newCountry;
	}*/
	while (currentCountry->next != NULL && strcmp(currentCountry->next->name, newCountry->name)< 0) {
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
	if (newCity->population < cityroot -> population && strcmp(newCity->name, cityroot->name) > 0) {
		cityroot->left = insertCityTree(cityroot->left, newCity);
	}
	else if(newCity->population <= cityroot->population && strcmp(newCity->name, cityroot->name) > 0){
		cityroot->right = insertCityTree(cityroot->right,newCity);

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