#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "tree.h"
#include "errors.h"

int MD(Branch current) {
	char name[MAX_NAME] = { 0 };
	Branch newDir = (Branch)malloc(sizeof(Tree));

	if (!newDir) {
		printf("\nAllocation error!\n");
		return ALLOCATION_ERROR;
	}
	newDir->child = NULL;
	newDir->sibling = NULL;

	scanf(" %s", newDir->name);
	
	current->child = Insert(current->child, newDir);

	return EXIT_SUCCESS;
}

Branch Insert(Branch P, Branch Q) {
	if (NULL == P) {
		return Q;
	}

	if (strcmp(P->name, Q->name) > 0) {
		Q->sibling = P;
		return Q;
	}

	P->sibling = Insert(P->sibling, Q);
	return P;
}

Branch DeallocationTree(Branch P) {
	if (NULL == P)
		return NULL;

	DeallocationTree(P->sibling);
	DeallocationTree(P->child);
	free(P);

	return NULL;
}