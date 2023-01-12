#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "textfile.h"
#include "errors.h"

int WriteInorderInFile(Branch Root, char* filename) {
	FILE* fp = NULL;
	fp = fopen(filename, "w");

	FILE_Inorder(Root, fp);
	fprintf(fp, "\n");

	fclose(fp);

	return EXIT_SUCCESS;
}

int FILE_Inorder(Branch Root, FILE* fp) {
	if (NULL == Root)
		return NULL;

	FILE_Inorder(Root->L,fp);
	fprintf(fp, "%d ", Root->num);
	FILE_Inorder(Root->R,fp);

	return EXIT_SUCCESS;
}