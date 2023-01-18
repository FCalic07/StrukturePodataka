#pragma once

#include "constants.h"
#include "city_list.h"

struct _country_b;
typedef struct _country_b* Branch_b;
typedef struct _country_b {
    char country_name[MAX_NAME];
    Branch_b L;
    Branch_b D;
    City head;
}Country;

int CityFile(Branch_b el, char* fileName);
Branch_b CountryFile(Branch_b root, char* fileName);
Branch_b Tree(Branch_b root, char* imeD, char* fileName);
Branch_b CreateTree(char* imeD);
int Print_Country(Branch_b root);
int FreeAll(Branch_b root);
