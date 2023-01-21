#pragma once

struct _binarytree;
typedef struct _binarytree* Branch;
typedef struct _binarytree {
	int num;
	Branch L;
	Branch R;
}BinaryTree;

struct _queue;
typedef struct _queue* Position;
typedef struct _queue {
	Branch P;
	Position Next;
}Queue;

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
int LevelOrder(Branch Root); //vise memorije zbog queue ali brze i to je u prednosti
Position FindLast(Position Head);
int LevelOrder1(Branch Root); //lo1 height i printlvl, manje memorije ali spori
int Height(Branch Root);
int PrintLevel(Branch Root, int level);
int Deallocation(Branch Root);

