#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "querry_b).h"
#include "constants.h"

int Querry_Country(Branch_b root)
{
    char name[MAX_NAME] = { 0 };
    int num = 0, i = 0;
    Branch_b temp = NULL;

    printf("What country you want to search?\n-> ");
    scanf(" %s", name);
    temp = Querry_Tree(root, name);
    if (!temp)
    {
        printf("Country does not exist!\n");
        return CLOSE_QUERRY;
    }

    printf("Enter number for comparision: \n");
    scanf(" %d", &num);
    Querry_City(&temp->head, num, &i);

    return EXIT_SUCCESS;
}

Branch_b Querry_Tree(Branch_b root, char* ime)
{
    if (NULL == root)
    {
        return NULL;
    }

    else if (strcmp(root->country_name, ime) == 0)
        return root;

    else if (strcmp(root->country_name, ime) > 0)
        root = Querry_Tree(root->L, ime);

    else
        root = Querry_Tree(root->D, ime);

    return root;

}

int Querry_City(Position_b head, int broj, int* i)
{
    while (head->next)
    {
        if (head->next->population > broj)
        {
            (*i)++;
            printf("%s\n", head->next->city_name);
        }
        head = head->next;
    }

    return EXIT_SUCCESS;
}