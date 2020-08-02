#include "../comparisonOfTree.h"

bool equalGraphs(mathTree::mathNode *tree, mathTree::mathNode *templateTree, typeReplacement *replace, bool inReplace)
{
	if (tree->arg == templateTree->arg && (templateTree->type != mathTree::mathNode::Types::VAR || inReplace))
	{
		if (templateTree->arg == "+" || templateTree->arg == "*")
			if (equalGraphs(tree->params[0], templateTree->params[0], replace, inReplace) ||
				equalGraphs(tree->params[1], templateTree->params[1], replace, inReplace) ||
				equalGraphs(tree->params[1], templateTree->params[0], replace, inReplace) ||
				equalGraphs(tree->params[0], templateTree->params[1], replace, inReplace))
				return true;
			else
				return false;

		for (int i(0); i < templateTree->params.size(); i++)
			if (!equalGraphs(tree->params[i], templateTree->params[i], replace, inReplace))
				return false;
		return true;
	}
	else if (templateTree->type == mathTree::mathNode::Types::VAR && !inReplace)
	{
		bool existReplacement = false;
		for (int i(0); i < replace->size(); i++)
			if (templateTree->arg == replace->at(i).first)
			{
				existReplacement = true;
				return equalGraphs(tree, replace->at(i).second, replace, true);
			}
		if (!existReplacement)
		{
			replace->push_back(std::pair<std::string, mathTree::mathNode *>(templateTree->arg, tree));
			return true;
		}
	}

	return false;
}

mathTree::mathNode *findSubgraph(mathTree::mathNode *baseGraph, mathTree::mathNode *templateGraph, typeReplacement *replace)
{
	if (equalGraphs(baseGraph, templateGraph, replace))
		return baseGraph;
	else
		for (int i(0); i < baseGraph->params.size(); i++)
		{
			mathTree::mathNode *retRecursion = findSubgraph(baseGraph->params[i], templateGraph, replace);
			if (retRecursion)
				return retRecursion;
		}
	return nullptr;
}

void replace(mathTree::mathNode *forReplace, mathTree::mathNode *templateTree, typeReplacement *replace)
{

}
