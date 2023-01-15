#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "country_list.h"
#include "constants.h"

Position CreateNewCountry(char* country_name, char* country_filename) {
	Position newCountry = (Position)malloc(sizeof(CountryList));

	if (!newCountry) {
		perror;
		return ALLOCATION_ERROR;
	}

	newCountry->Next = NULL;
	newCountry->Root = NULL;
	strcpy(newCountry->country_name, country_name);

	return newCountry;
}

int CountryEntry(Position Head, Position newCountry) { //sortirani unos
	Position TEMP = Head;

	while (TEMP) {
		if (!TEMP->Next || (strcmp(TEMP->country_name, newCountry->country_name) > 0)) {
			newCountry->Next = TEMP->Next;
			TEMP->Next = newCountry;
			break;
		}
		TEMP = TEMP->Next;
	}

	return EXIT_SUCCESS;
}

int PrintCountries(Position Head) {
	Position Country = Head->Next;

	while (Country) {
		printf("\n- %s", Country->country_name);
		Country = Country->Next;
	}

	return EXIT_SUCCESS;
}

Position FindCountry(Position Head, char* country_name) {
	Position Country = Head->Next;

	while (Country) {
		if (strcmp(Country->country_name, country_name) == 0)
			return Country;
		Country = Country->Next;
	}
	return Country;
}

int DeleteAfter(Position P) {

	Position TEMP = P->Next;
	P->Next = TEMP->Next;
	free(TEMP);

	return EXIT_SUCCESS;
}

int DeallocationList(Position Head) {

	while (Head->Next) {
		DeallocationTree(Head->Root);
		DeleteAfter(Head);
	}
	Head = NULL;

	return EXIT_SUCCESS;
}