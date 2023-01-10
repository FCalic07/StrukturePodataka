#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binarytree.h"

int main() {
	int sum = 0, i = 0;
	/* napravi stablo, niz, dodaj brojeve u stablo*/
	int niz[10] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	int niz2[10] = {0};
	Branch Root = NULL;
	srand(time(NULL));

	Root = insert(Root,niz);

	Inorder(Root); //Test radil dobro

	/*pod a gotovo*/
	sum = NodeSum(Root);
	/*funkcija replace*/
	printf("\nnew root should be : %d\n", sum);

	Root = replace(Root);

	Inorder(Root);
	/*gotovo lol*/
	printf("\n\n");
	/*MORAS OBRISAT ROOT*/;

	Root = NULL;

	/*rand od 10 do 90*/
	for (i = 0; i < 10; i++) {
		niz[i] = rand() % 79 + 11;
	}
	Root = insert(Root, niz);
	Inorder(Root);
	printf("\n\n");
	Root = replace(Root);
	Inorder(Root);

	
	return EXIT_SUCCESS;
}
