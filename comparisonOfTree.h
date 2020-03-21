#pragma once

#include "mathTree.h"

typedef std::vector<std::pair<std::string, mathTree::mathNode *>> typeReplacement;

bool equalGraphs(mathTree::mathNode *, mathTree::mathNode *, typeReplacement *, bool = false);