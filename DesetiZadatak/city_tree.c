#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "city_tree.h"


Branch CreateNewCity(char* city_name, int population) {
	Branch newCity = (Branch)malloc(sizeof(CityTree));

	if (!newCity) {
		perror;
		return ALLOCATION_ERROR;
	}
	newCity->L = NULL;
	newCity->R = NULL;
	strcpy(newCity->name, city_name);
	newCity->population = population;

	return newCity;
}

Branch CityEntry(Branch Root, Branch newCity) {
	if (NULL == Root) {
		return newCity;
	}

	if (newCity->population > Root->population) {
		Root->L = CityEntry(Root->L, newCity);
	}
	else if (newCity->population < Root->population) {
		Root->R = CityEntry(Root->R, newCity);
	}
	else if (strcmp(newCity->name, Root->name) > 0) {
		Root->L = CityEntry(Root->L, newCity);
	}
	else if (strcmp(newCity->name, Root->name) < 0) {
		Root->R = CityEntry(Root->R, newCity);
	}
	else {
		free(newCity);
	}
	return Root;
}

int InorderPrint(Branch City) {
	if (NULL == City)
		return NULL;

	InorderPrint(City->L);
	printf("\t%s  %d\n", City->name, City->population);
	InorderPrint(City->R);

	return EXIT_SUCCESS;
}

int DeallocationTree(Branch Root) {
	if (NULL == Root)
		return EXIT_SUCCESS;

	DeallocationTree(Root->R);
	DeallocationTree(Root->L);
	free(Root);

	return EXIT_SUCCESS;

}