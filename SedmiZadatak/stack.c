#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "tree.h"
#include "errors.h"

int Push(Position Head, Branch dir) {
	Position Last = NULL;
	Position nP = NULL;

	nP = (Position)malloc(sizeof(Stack));
	if (!nP) {
		printf("\nAllocation error!");
		return ALLOCATION_ERROR;
	}
	nP->directory = dir;
	nP->Next = NULL;

	Last = FindLast(Head);
	Last->Next = nP;
	
	return EXIT_SUCCESS;
}

Position FindLast(Position Head) {
	Position TEMP = Head;

	while (TEMP->Next) {
		TEMP = TEMP->Next;
	}
	return TEMP;
}

int Pop(Position Head) {
	Position Last = NULL;
	Last = FindLast(Head);

	Head->Next = Delete(Head->Next, Last);
	return EXIT_SUCCESS;
}

Position Delete(Position P, Position Q) {
	if (NULL == P)
		return NULL;

	if (P == Q) {
		Position Next = P->Next;
		free(P);
		return Next;
	}
	P->Next = Delete(P->Next, Q);
	return P;
}

Position DeallocationStack(Position P) {
	if (NULL == P)
		return NULL;

	DeallocationTree(P->Next);
	free(P);

	return NULL;
}
