#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "filehandling.h"
#include "constants.h"


int ReadStatesFromFile(Position Head, char* filename) {
	FILE* fp = NULL;
	Position newCountry = NULL;
	char country_name[MAX_NAME] = { 0 };
	char country_filename[MAX_FILENAME] = { 0 };
	int city_status = 0;

	fp = fopen(filename, "r");
	if (!fp) {
		perror("\nFile can't open!");
		return EXIT_FAILURE;
	}

	while (!feof(fp)) {
		fscanf(fp, " %s %s", country_name, country_filename);
		newCountry = CreateNewCountry(country_name, country_filename);

		if (!newCountry) {
			return EXIT_FAILURE;
		}

		CountryEntry(Head, newCountry);

		city_status = ReadCitiesFromFile(newCountry, country_filename);
		if (city_status) {
			printf("\nCan't open %s's file", newCountry->country_name);
		}
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int ReadCitiesFromFile(Position newCountry, char* country_filename) {
	FILE* fp = NULL;
	Branch newCity = NULL;
	int population = 0;
	char city_name[MAX_NAME] = { 0 };

	fp = fopen(country_filename, "r");
	if (!fp) {
		perror;
		return FILE_OPENING_ERROR;
	}

	while (!feof(fp)) {
		fscanf(fp, " %s %d", city_name, &population);
		newCity = CreateNewCity(city_name, population);

		if (!newCity) {
			return EXIT_FAILURE;
		}

		newCountry->Root = CityEntry(newCountry->Root, newCity);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}
