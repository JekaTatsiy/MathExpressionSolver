#pragma once

#include "mathTree.h"

bool equal(mathTree::mathNode *tree, mathTree::mathNode *templateTree, std::vector<std::pair<std::string, mathTree::mathNode *>> *replacement, bool inReplace);