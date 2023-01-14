#pragma once

#include "country_list.h"

char* GetFilename();
int ReadStatesFromFile(Position Head, char* filename);
int ReadCitiesFromFile(Position newCountry, char* country_filename);
