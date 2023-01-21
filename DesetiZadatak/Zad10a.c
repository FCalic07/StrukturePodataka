#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "filehandling.h"
#include "querry_a).h"

int Zadatak10a() {
	Position Head[prime];
	int status = 23;
	
	for (int i = 0; i < prime; i++) {
		Head[i] = (Position)malloc(sizeof(CountryList));
		Head[i]->Root = NULL; Head[i]->Next = NULL;
		strcpy(Head[i]->country_name, "");
	}

	char filename[MAX_NAME] = { 0 };
	FILE* fp = NULL;
	int file_status = 0;

	printf("\nPlease enter the <states> filename\nFilename: ");
	scanf(" %s", filename);
	
	file_status = ReadStatesFromFile(Head, filename);
	if (file_status) {
		return FILE_OPENING_ERROR;
	}

	PrintAll(Head);

	CityQuerry(Head);

	//Dealokacija
	status = DeallocationList(Head);
	if (NULL == status) {
		printf("\nDeallocation successfull!");
	}
	else {
		printf("\nDeallocation unsuccessfull!");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int PrintAll(Position Head[]) {
	for (int i = 0; i < prime; i++) {
		Position Country = Head[i]->Next;
		Branch City = NULL;

		while (Country) {
			printf("\n%s's cities found\n", Country->country_name);

			City = Country->Root;
			InorderPrint(City);

			Country = Country->Next;
		}
	}
	return EXIT_SUCCESS;
}