#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "city_list.h"
#include "constants.h"


int Sort(Position_b head, char* city_name, int population)
{
    Position_b tempPrev = head;
    Position_b tempNext = head->next;

    while (tempNext)
    {
        if (tempNext->population > population)
        {
            Create_Country(tempPrev, city_name, population);
            return EXIT_SUCCESS;
        }

        else if (tempNext->population == population)
            if (strcmp(tempNext->city_name, city_name) > 0)
            {
                Create_Country(tempPrev, city_name, population);
                return EXIT_SUCCESS;
            }

        tempPrev = tempPrev->next;
        tempNext = tempNext->next;
    }

    Create_Country(tempPrev, city_name, population);

    return EXIT_SUCCESS;
}

int Create_Country(Position_b el, char* city_name, int population)
{
    Position_b new = NULL;

    new = (Position_b)malloc(sizeof(City));
    if (!new)
    {
        perror("Allocation ERROR!\n");
        return ALLOCATION_ERROR;
    }

    strcpy(new->city_name, city_name);
    new->population = population;
    new->next = NULL;

    Insert(el, new);

    return EXIT_SUCCESS;
}

int Insert(Position_b el, Position_b new)
{
    new->next = el->next;
    el->next = new;

    return EXIT_SUCCESS;
}

int Print_City(Position_b head)
{
    while (head->next)
    {
        printf("    %s\n", head->next->city_name);
        head = head->next;
    }

    return EXIT_SUCCESS;
}

int FreeList(Position_b head)
{
    Position_b temp = NULL;

    while (head->next)
    {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    return EXIT_SUCCESS;
}

