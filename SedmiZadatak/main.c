#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"


int main() {
	Tree ZerothRoot = { .name = "C:",.child = NULL,.sibling = NULL };
	Branch Root = &ZerothRoot;
	Stack ZerothStack = { .directory = Root,.Next = NULL };
	Position Head = &ZerothStack;

	int status = NULL;

	WelcomeMessage();

	while(!status){
		status = Menu(Root, Head);
	} 

	//dealokacija
	Root->child = DeallocationTree(Root->child);
	Head->Next = DeallocationStack(Head->Next);

	return EXIT_SUCCESS;
}

int WelcomeMessage() {

	printf("Mirkosoft Ponistra [Version -10.0.19043.1526]"
		"\n(c) Mirkosoft Drustvo s ogranicenom odgovornoscu. All rights reserved.\n");

	return EXIT_SUCCESS;
}