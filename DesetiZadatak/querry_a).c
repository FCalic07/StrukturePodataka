#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "querry_a).h"

int CityQuerry(Position Head) {
	char country_name[MAX_NAME] = { 0 };
	Position Country = NULL;
	Branch City = NULL;
	int min_population = 0, status = 0;

	status = CityQuerryIntroduction();
	if (status) {
		return EXIT_SUCCESS;
	}

	PrintCountries(Head);

	while (1) {
		printf("\nChoose the country -> ");
		scanf(" %s", country_name);
		Country = FindCountry(Head, country_name);

		if (!Country) {
			printf("\nCountry %s not found. Please try again.\n", country_name);
		}
		else {
			break;
		}
	}

	printf("\nEnter minimal city population -> ");
	scanf(" %d", &min_population);

	MinPopulationQuerry_City(Country->Root, min_population);

	return EXIT_SUCCESS;
}

int MinPopulationQuerry_City(Branch Root, int min) {
	if (NULL == Root)
		return NULL;

	if (Root->population < min) {
		MinPopulationQuerry_City(Root->L, min);
	}
	else if (Root->population >= min) {
		MinPopulationQuerry_City(Root->L, min);
		printf("\n%s  %d", Root->name, Root->population);
		MinPopulationQuerry_City(Root->R, min);
	}

	return EXIT_SUCCESS;
}

int CityQuerryIntroduction() {
	char choice = 0;
	int status = 0;

	printf("\nDo you want to filter cities (Y/N)\n");

	while (!status) {
		printf("-> ");
		scanf(" %c", &choice);
		choice = toupper(choice);

		switch (choice) {
		case 'Y':
			status = 1;
			break;
		case 'N':
			return CLOSE_QUERRY;
		default:
			printf("Choose with either 'Y' or 'N' !\n");
			break;
		}
	}

	printf("\nHere you can filter cities by country and minimal population\n"
		"\nFirst enter the country name you want and then"
		"\nthe number of minimal population you want"
		"\nCities will be printed in descending order"
		"\nCountries:");

	return EXIT_SUCCESS;
}