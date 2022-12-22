#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int menu_mode = 1; //on		ovdje ju definiraš

int main() {
	Branch Root = NULL;
	int status = sizeof(int); //fazon svaki put novi nacin da nije nula

	while (menu_mode) {

		Root = Menu(Root);

	}

	status = Deallocation(Root);
	if (status == 0)
		printf("\nDeallocation successfull!\n");
	else
		printf("\nDeallocation error!\n");


	return EXIT_SUCCESS;
}