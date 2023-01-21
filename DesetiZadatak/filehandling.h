#pragma once

#include "country_list.h"

int ReadStatesFromFile(Position Head[], char* filename);
int ReadCitiesFromFile(Position newCountry, char* country_filename);
int HashKey(char* country_name);
