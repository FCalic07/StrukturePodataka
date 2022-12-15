#pragma once

#include "tree.h"
#include "stack.h"

int Menu(Branch Root, Position Head);
int PrintCurrentFolder(Position Head);
int DIR(Branch current, Position Head);
Branch CD(Branch current, Position Head);
Branch CD_BACK(Branch current, Position Head);

