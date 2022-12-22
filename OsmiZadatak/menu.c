#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "menu.h"
#include "errors.h"

extern int menu_mode; // sa extern kazes da postoji negdje (vec postavljena na vrijednost)

Branch Menu(Branch Root) {
	int choice = 0;

	PrintOptions();
	choice = CheckInput();

	system("cls"); //da pocisti staro

	switch (choice) {
	case(0):
		menu_mode = 0; //off
		break;
	case(1):
		Root = EnterElement(Root);
		break;
	case(2):
		FindingElement(Root);
		break;
	case(3):
		Root = DeleteElement(Root);
		break;
	case(4):
		Inorder(Root);
		break;
	case(5):
		Preorder(Root);
		break;
	case(6):
		Postorder(Root);
		break;
	case(7):
		LevelOrder(Root);
		break;
	default:
		printf("\nCommand not recognized!\n");
	}

	return Root;
}

int FindingElement(Branch Root) {
	int num = 0;
	Branch TEMP = Root;
	printf("\nEnter element you want to find: ");
	scanf(" %d", &num);

	TEMP = FindElement(TEMP, num);

	if (!TEMP) {
		printf("\nNo such element!\n");
	}
	else
		printf("\nElement: %d\n", TEMP->num);

	return EXIT_SUCCESS;
}

int PrintOptions() {

	printf("\n ------ OPTIONS ------"
		"\n Enter a element   - 1"
		"\n Find a element    - 2"
		"\n Delete a element  - 3"
		"\n Inorder           - 4"
		"\n Preorder          - 5"
		"\n Postorder         - 6"
		"\n Level order       - 7"
		"\n         Exit      - 0"
		"\n ---------------------\n");

	return EXIT_SUCCESS;
}

int CheckInput() {
	int num = 0;
	char input[MAX] = { 0 };

	while (!num) {
		
		printf("\nOption: ");
		scanf(" %s", input);

		if ( sscanf(input, "%d", &num) != 1) {
			num = INPUT_ERROR;
			printf("\nInvalid input!\n");
			continue;
		}
		else
			return num;
	}
}