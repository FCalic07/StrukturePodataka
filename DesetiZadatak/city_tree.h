#pragma once

#include "constants.h"

struct _citytree;
typedef struct _citytree* Branch;
typedef struct _citytree {
	char name[MAX_NAME];
	int population;
	Branch L;
	Branch R;
}CityTree;

Branch CreateNewCity(char* city_name, int population);
Branch CityEntry(Branch Root, Branch newCity);
int InorderPrint(Branch City);
int DeallocationTree(Branch Root);