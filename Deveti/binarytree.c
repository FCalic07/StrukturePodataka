#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"

#define ALLOCATION_ERROR (-1) //ovo u drugi header i malo ovaj insert promijenit ime i uljepsat

Branch insert(Branch Root, int niz[]) {
	Branch newElement = NULL;
	int i = 0;

	for (i = 0; i < 10; i++) {
		newElement = (Branch)malloc(sizeof(BinaryTree));

		if (!newElement) {
			perror("\nError: ");
			return ALLOCATION_ERROR;
		}
		newElement->L = NULL;
		newElement->R = NULL;
		newElement->num = niz[i];

		Root = Insert(Root, newElement);
	}
	return Root;
}

Branch Insert(Branch P, Branch Q) {
	if (NULL == P) {
		return Q;
	}
	if (P->num <= Q->num) {
		P->L = Insert(P->L, Q);
	}
	else if (P->num > Q->num) {
		P->R = Insert(P->R, Q);
	}
	else {
		free(Q);
	}
	return P;
}

int Inorder(Branch Root) {
	if (NULL == Root)
		return NULL;

	Inorder(Root->L);
	printf("%d ", Root->num);
	Inorder(Root->R);

	return EXIT_SUCCESS;
}

Branch replace(Branch P) {
	if (NULL == P)
		return P;

	P->num = NodeSum(P) - P->num;
	
	P->L = replace(P->L);
	P->R = replace(P->R);

	return P;
}

int NodeSum(Branch P){
	int sum = 0, left = 0, right = 0;

	if (P->L)
		left = NodeSum(P->L);
	if (P->R)
		right = NodeSum(P->R);
	if (!P->L && !P->R)
		return P->num;

	sum = left + right + P->num;
	return sum;
}