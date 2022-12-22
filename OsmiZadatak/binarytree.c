#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"
#include "errors.h"

Branch EnterElement(Branch Root) {
	Branch newElement = NULL;

	newElement = (Branch)malloc(sizeof(BinaryTree));

	if (!newElement) {
		perror("\nError: ");
		return ALLOCATION_ERROR;
	}
	newElement->L = NULL;
	newElement->R = NULL;
	
	printf("\nEnter number: ");
	scanf(" %d", &newElement->num);

	Root = Insert(Root, newElement);

	return Root;
}

Branch Insert(Branch P, Branch Q) {
	if (NULL == P) {
		return Q;
	}
	if (P->num < Q->num) {
		P->R = Insert(P->R, Q);
	}
	else if (P->num > Q->num) {
		P->L = Insert(P->L, Q);
	}
	else {
		free(Q);
	}
	return P;
}

Branch DeleteElement(Branch Root) {
	int num = 0;

	printf("\nEnter number you want to delete: ");
	scanf(" %d", &num);
		//sta ako nije broj
	Root = Delete(Root, num);

	return Root;
}

Branch Delete(Branch P, int num) {
	Branch TEMP = NULL;

	if (NULL == P) {
		return NULL;
	}
	if (P->num < num) {
		P->R = Delete(P->R, num);
	}
	else if (P->num > num) {
		P->L = Delete(P->L, num);
	}
	else {
		if (P->L) {
			TEMP = findMax(P->L);
			P->num = TEMP->num;
			P->L = Delete(P->L, TEMP->num);
		}
		else if (P->R) {
			TEMP = findMin(P->R);
			P->num = TEMP->num;
			P->R = Delete(P->R, TEMP->num);
		}
		else {
			free(P);
			return NULL;
		}
	}
	return P;
}

Branch findMax(Branch P) {
	Branch TEMP = P;

	while (TEMP->R) {
		TEMP = TEMP->R;
	}
	return TEMP;
}

Branch findMin(Branch P) {
	Branch TEMP = P;

	while (TEMP->L) {
		TEMP = TEMP->L;
	}
	return TEMP;
}

Branch FindElement(Branch P, int num) {
	if (NULL == P) {
		return NULL;
	}
	else if (num > P->num) {
		FindElement(P->R, num);
	}
	else if (num < P->num) {
		FindElement(P->L, num);
	}
	else
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

int Preorder(Branch Root) {
	if (NULL == Root)
		return NULL;

	printf("%d ", Root->num);
	Preorder(Root->L);
	Preorder(Root->R);

	return EXIT_SUCCESS;
}

int Postorder(Branch Root) {
	if (Root == NULL)
		return NULL;

	Postorder(Root->L);
	Postorder(Root->R);
	printf("%d ", Root->num);

	return EXIT_SUCCESS;
}

int LevelOrder(Branch Root) {
	int height = 0, i = 0;
	height = Height(Root);

	for (i = 1; i <= height; i++) {
		PrintLevel(Root, i);
	}

	return EXIT_SUCCESS;
}

int Height(Branch Root){
	int Lheight = 0;
	int Rheight = 0;

	if (NULL == Root)
		return NULL;
	else{
		Lheight = Height(Root->L);
		Rheight = Height(Root->R);

		if (Lheight >= Rheight)
			return(Lheight + 1);
		else
			return (Rheight + 1);
	}
	return EXIT_SUCCESS;
}

int PrintLevel(Branch Root, int level) {
	if (NULL == Root)
		return NULL;

	if (1 == level)
		printf("%d ", Root->num);

	else if (level > 1)
	{
		PrintLevel(Root->L, level - 1);
		PrintLevel(Root->R, level - 1);
	}

	return EXIT_SUCCESS;
}

int Deallocation(Branch Root) {
	if (NULL == Root)
		return EXIT_SUCCESS;

	Deallocation(Root->L);
	Deallocation(Root->R);
	free(Root);

	return EXIT_SUCCESS;
}