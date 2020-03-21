#include "comparisonOfTree.h"

bool equalGraphs(mathNode *tree, mathNode *templateTree, vector<pair<string, mathNode *>> *replacement, bool inReplace)
{
	if (tree->getAction() == templateTree->getAction() && (templateTree->getTypeValue() != VAR || inReplace))
	{
		if (templateTree->getAction() == "+" || templateTree->getAction() == "*")
			if (equalGraphs(tree->getParam(0), templateTree->getParam(0), replacement, inReplace) &&
				equalGraphs(tree->getParam(1), templateTree->getParam(1), replacement, inReplace))
				return true;
			else if (equalGraphs(tree->getParam(1), templateTree->getParam(0), replacement, inReplace) && equalGraphs(tree->getParam(0), templateTree->getParam(1), replacement, inReplace))
				return true;
			else
				return false;

		for (int i(0); i < templateTree->getParamsSize(); i++)
			if (!equalGraphs(tree->getParam(i), templateTree->getParam(i), replacement, inReplace))
				return false;
		return true;
	}
	else if (templateTree->getTypeValue() == VAR && !inReplace)
	{
		bool existReplacement = false;
		for (int i(0); i < replacement->size(); i++)
			if (templateTree->getAction() == replacement->at(i).first)
			{
				existReplacement = true;
				return equalGraphs(tree, replacement->at(i).second, replacement, true); 
			}
		if (!existReplacement)
		{
			replacement->push_back(pair<string, mathNode *>(templateTree->getAction(), tree));
			return true;
		}
	}

	return false;
}