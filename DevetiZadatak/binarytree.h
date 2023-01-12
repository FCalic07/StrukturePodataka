#pragma once

struct _binarytree;
typedef struct _binarytree* Branch;
typedef struct _binarytree {
	int num;
	Branch L;
	Branch R;
}BinaryTree;

Branch insert(Branch Root, int array[], int size);
Branch CreateElement(int num);
Branch Insert(Branch P, Branch Q);
int Inorder(Branch Root);
Branch replace(Branch P);
int NodeSum(Branch P);
int Deallocation(Branch Root);