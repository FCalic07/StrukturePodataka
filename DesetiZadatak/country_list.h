#pragma once
#include "constants.h"
#include "city_tree.h"

struct _country;
typedef struct _country* Position;
typedef struct _country {
	char country_name[MAX_NAME];
	Position Next;
	Branch Root;
}CountryList;

Position CreateNewCountry(char* country_name, char* country_filename);
int CountryEntry(Position Head, Position newCountry);
int PrintCountries(Position Head);
Position FindCountry(Position Head, char* country_name);
int DeleteAfter(Position P);
int DeallocationList(Position Head);
