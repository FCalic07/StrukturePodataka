#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "country_tree.h"

int CityFile(Branch_b el, char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    char city_name[MAX_NAME] = { 0 };
    int population = 0;

    if (!fp)
    {
        printf("File is not opened\n");
        return FILE_OPENING_ERROR;
    }

    while (!feof(fp))
    {
        if (fscanf(fp, " %s %d", city_name, &population) == 2)
            Sort(&el->head, city_name, population);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

Branch_b CountryFile(Branch_b root, char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    char temp_country_name[MAX_NAME] = { 0 };
    char filename_city[MAX_NAME] = { 0 };

    if (!fp)
    {
        printf("Datoteka nije otvorena!\n");
        return FILE_OPENING_ERROR2;
    }

    while (!feof(fp))
    {
        if (fscanf(fp, " %s %s", temp_country_name, filename_city) == 2)
            root = Tree(root, temp_country_name, filename_city);
    }

    fclose(fp);

    return root;
}

Branch_b Tree(Branch_b root, char* country_name, char* fileName)
{
    if (!root)
    {
        root = CreateTree(country_name);
        CityFile(root, fileName);
    }

    else if (strcmp(root->country_name, country_name) > 0)
        root->L = Tree(root->L, country_name, fileName);

    else
        root->D = Tree(root->D, country_name, fileName);

    return root;
}

Branch_b CreateTree(char* country_name)
{
    Branch_b newTree = NULL;
    newTree = (Branch_b)malloc(sizeof(Country));
    if (!newTree)
    {
        printf("\nAllocation ERROR!\n");
        return ALLOCATION_ERROR;
    }

    strcpy(newTree->country_name, country_name);
    strcpy(newTree->head.city_name, "");
    newTree->head.population = 0;
    newTree->head.next = NULL;
    newTree->L = NULL;
    newTree->D = NULL;

    return newTree;
}

int Print_Country(Branch_b root)
{
    if (root->L)
        Print_Country(root->L);

    printf("%s\n", root->country_name);
    Print_City(&root->head);

    if (root->D)
        Print_Country(root->D);

    return EXIT_SUCCESS;
}

int FreeAll(Branch_b root)
{
    if (!root)
        return EXIT_SUCCESS;

    FreeList(&root->head);

    FreeAll(root->L);

    FreeAll(root->D);

    free(root);

    return EXIT_SUCCESS;
}

