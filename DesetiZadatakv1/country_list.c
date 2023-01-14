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