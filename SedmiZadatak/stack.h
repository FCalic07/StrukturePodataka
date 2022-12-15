#pragma once
#include "tree.h"

struct _stack;
typedef struct _stack* Position;
typedef struct _stack {
	Branch directory;
	Position Next;
}Stack;

int Push(Position Head, Branch dir);
int Pop(Position Head);
Position Delete(Position P, Position Q);
Position FindLast(Position Head);
Position DeallocationStack(Position P);