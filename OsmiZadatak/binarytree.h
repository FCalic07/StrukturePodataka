#pragma once

struct _binarytree;
typedef struct _binarytree* Branch;
typedef struct _binarytree {
	int num;
	Branch L;
	Branch R;
}BinaryTree;

Branch EnterElement(Branch Root);
Branch Insert(Branch P, Branch Q);
Branch DeleteElement(Branch Root);
Branch Delete(Branch P, int num);
Branch findMax(Branch P);
Branch findMin(Branch P);
Branch FindElement(Branch P, int num);
int Inorder(Branch Root);
int Preorder(Branch Root);
int Postorder(Branch Root);
int LevelOrder(Branch Root);
int Height(Branch Root);
int PrintLevel(Branch Root, int level);
int Deallocation(Branch Root);

