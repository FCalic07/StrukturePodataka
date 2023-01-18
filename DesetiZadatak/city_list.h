#pragma once

#include "constants.h"

struct _city;
typedef struct _city* Position_b;
typedef struct _city {
    char city_name[MAX_NAME];
    int population;
    Position_b next;
}City;


int Sort(Position_b head, char* imeG, int broj);
int Create_Country(Position_b el, char* imeG, int broj);
int Insert(Position_b el, Position_b new);
int Print_City(Position_b head);
int FreeList(Position_b head);



