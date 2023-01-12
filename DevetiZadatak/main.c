#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binarytree.h"
#include "textfile.h"

#define MAX_SIZE (64)

int* RandArray(int size);

int main() {
	Branch Root = NULL;
	Branch Root2 = NULL;

	int deall1 = 0, deall2 = 0, size = 10;
	int predef_arr[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	int* rand_arr;
	char filename[MAX_FILENAME_SIZE] = { 0 };

	printf("\nInsert function for a predefined array printed inorder\n");
	Root = insert(Root, predef_arr, size);
	Inorder(Root);
	
	printf("\nReplace function for the array above printed inorder\n");
	Root = replace(Root);
	Inorder(Root);

	printf("\n\nInsert function for a rand() array"
		"printed inorder in console and in file\n");

	printf("\nPlease enter txt filename: "); scanf(" %s", filename);
	printf("Enter size of array: "); scanf(" %d", &size);

	rand_arr = RandArray(size);
	Root2 = insert(Root2, rand_arr, size);
	Inorder(Root2);
	WriteInorderInFile(Root2, filename);

	printf("\nAnd finally, replace function, printed in console and in file\n");
	Root2 = replace(Root2);
	Inorder(Root2);
	WriteInorderInFile(Root2, filename);

	//deallocation
	deall1 = Deallocation(Root);
	deall2 = Deallocation(Root2);

	if (deall1 == 0 && deall2 == 0)
		printf("\n\nDeallocation successfull!\n");
	else
		printf("\n\nDeallocation error!\n");

	return EXIT_SUCCESS;
}

int* RandArray(int size) {
	srand(time(NULL));
	int i = 0;


	int* array = (int*)malloc(size * sizeof(int));

	for (i = 0; i < size; i++) {
		array[i] = (rand() % 79) + 11;
	}

	return array;
}