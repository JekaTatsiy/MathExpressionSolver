#include "comparisonOfTree.h"

bool equalGraphs(mathTree::mathNode *tree, mathTree::mathNode *templateTree, std::vector<std::pair<std::string, mathTree::mathNode *>> *replacement, bool inReplace)
{
	if (tree->arg == templateTree->arg && (templateTree->type != mathTree::mathNode::Types::VAR || inReplace))
	{
		if (templateTree->arg == "+" || templateTree->arg == "*")
			if (equalGraphs(tree->params[0], templateTree->params[0], replacement, inReplace) &&
				equalGraphs(tree->params[1], templateTree->params[1], replacement, inReplace))
				return true;
			else if (equalGraphs(tree->params[1], templateTree->params[0], replacement, inReplace) && equalGraphs(tree->params[0], templateTree->params[1], replacement, inReplace))
				return true;
			else
				return false;

		for (int i(0); i < templateTree->params.size(); i++)
			if (!equalGraphs(tree->params[i], templateTree->params[i], replacement, inReplace))
				return false;
		return true;
	}
	else if (templateTree->type == mathTree::mathNode::Types::VAR && !inReplace)
	{
		bool existReplacement = false;
		for (int i(0); i < replacement->size(); i++)
			if (templateTree->arg == replacement->at(i).first)
			{
				existReplacement = true;
				return equalGraphs(tree, replacement->at(i).second, replacement, true);
			}
		if (!existReplacement)
		{
			replacement->push_back(std::pair<std::string, mathTree::mathNode *>(templateTree->arg, tree));
			return true;
		}
	}

	return false;
}