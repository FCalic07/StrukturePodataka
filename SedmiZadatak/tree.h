#pragma once

#define MAX_NAME (128)

struct _tree;
typedef struct _tree* Branch;
typedef struct _tree {
	char name[MAX_NAME];
	Branch child;
	Branch sibling;
}Tree;

int MD(Branch current);
Branch Insert(Branch P, Branch Q);
Branch DeallocationTree(Branch P);
