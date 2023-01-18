#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Zad10a.h"
#include "Zad10b.h" 

static char Choice();


int main() {

	switch (Choice()) {
	case('A'):
		return Zadatak10a();
	case('B'):
		return Zadatak10b();
	default:
		break;
	}

	return EXIT_SUCCESS;
}

static char Choice() {
	char choice = 0;

	while (1) {
		printf("Choose the option\n"
			"A\n"
			"B\n"
			"0 - Exit\n"
			"\n-> ");

		choice = toupper(getchar());

		switch (choice)
		{
		case 'A':
		case 'B':
		case '0':
			return choice;
		default:
			printf("Wrong choice! Try again!\n");
			break;
		}

	}
}