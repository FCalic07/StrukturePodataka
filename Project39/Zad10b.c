#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "country_tree.h"
#include "querry_b).h"


#include "Zad10b.h"


int Zadatak10b()
{
    Branch_b root = NULL;
    char filename[MAX_FILENAME] = { 0 };
    int status = 12;

    printf("\nFrom which file you want to read countries:");
    scanf(" %s", filename);
    root = CountryFile(root, filename);

    Print_Country(root);

    Querry_Country(root);

    status = FreeAll(root);
    if (NULL == status) {
        printf("\nDeallocation successfull!");
    }
    else {
        printf("\nDeallocation unsuccessfull!");
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}