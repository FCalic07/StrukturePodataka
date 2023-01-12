#pragma once

#include "binarytree.h"
#define MAX_FILENAME_SIZE (128)

int WriteInorderInFile(Branch Root, char* filename);
int FILE_Inorder(Branch Root, FILE* fp);
