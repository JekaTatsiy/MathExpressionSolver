#ifndef COMPARISON_OF_TREE_H
#define COMPARISON_OF_TREE_H

#include <vector>
#include <string>
#include <iostream>
#include "mathNode.h"
#include "mathTree.h"

typedef std::vector<std::pair<std::string, mathNode *>> typeReplacement;

bool equalGraphs(mathNode *, mathNode *, typeReplacement *, bool = false);

mathNode *findSubgraph(mathNode *, mathNode *, typeReplacement *);

void replace(mathNode *, mathNode *, typeReplacement *);

#endif
