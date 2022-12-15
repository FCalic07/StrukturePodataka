#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "menu.h"

#define while_on (1)
#define MAX_SIZE (128)
#define quit_program (-1)

int Menu(Branch Root, Position Head) {
	Branch current = Root;
	char entry[MAX_SIZE] = { 0 };

	while (while_on) {
		PrintCurrentFolder(Head);

		scanf(" %s", entry);

		if (strcmp(entry, "md") == 0)
			MD(current);

		else if (strcmp(entry, "cd") == 0)
			current = CD(current, Head);

		else if (strcmp(entry, "cd..") == 0)
			current = CD_BACK(current, Head);

		else if (strcmp(entry, "DIR") == 0)
			DIR(current, Head);

		else if (strcmp(entry, "exit") == 0)
			return quit_program;

		else 
			printf("''%s''  is not recognized as an internal or external command,"
			 "\noperable program or batch file.\n", entry);
	}

	return EXIT_SUCCESS;
}

int PrintCurrentFolder(Position Head) {
	Position TEMP = Head;

	while (TEMP) {
		printf("%s\\", TEMP->directory->name);
		TEMP = TEMP->Next;
	}

	return EXIT_SUCCESS;
}

int DIR(Branch current, Branch Head) {
	Branch TEMP = current->child;

	printf("\nDirectory of "); 
	PrintCurrentFolder(Head);
	printf("\n");

	while (TEMP) {
		printf("\n<DIR>\t%s", TEMP->name);
		TEMP = TEMP->sibling;
	}

	printf("\n\n");

	return EXIT_SUCCESS;
}

Branch CD(Branch current, Position Head) {
	char name[MAX_NAME] = { 0 };
	Branch TEMP = current->child;

	scanf(" %s", name);

	if (!TEMP) {
		printf("\nThe system cannot find the path specified.\n");
		return current;
	}
	else {
		while (TEMP) {
			if (strcmp(TEMP->name, name) == 0) {
				Push(Head, TEMP);
				return TEMP;
			}
			TEMP = TEMP->sibling;
		}
	}
}

Branch CD_BACK(Branch current, Position Head) {
	Branch Previous = NULL;

	if (!Head->Next)
		return current;

	Pop(Head);
	Previous = FindLast(Head)->directory;

	return Previous;
}
