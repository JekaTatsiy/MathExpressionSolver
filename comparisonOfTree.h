#pragma once

#include "mathTree.h"

typedef std::vector<std::pair<std::string, mathTree::mathNode *>> typeReplacement;

bool equal(mathTree::mathNode *, mathTree::mathNode *, std::vector<std::pair<std::string, mathTree::mathNode *>> *, bool);