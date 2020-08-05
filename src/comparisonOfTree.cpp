#include "../comparisonOfTree.h"

mathNode* existEqualSubgraph(mathNode *tree, mathNode *templ, bool wasCollision)
{
	if (templ->type==mathNode::Types::VAR)
	{
		return tree;
	}
	else if(tree->arg == templ->arg && tree->params.size()==tree->params.size())
	{
		for(int i=0;i<tree->params.size();i++)
			if(!existEqualSubgraph(tree->params[i],templ->params[i],true))
				return nullptr;
		return tree;
	}
	else if(!wasCollision)
	{
		mathNode* equal;
		for(auto i: tree->params)
			equal = existEqualSubgraph(i,templ);
				if(equal)
					return equal;		
	}
	return nullptr;
	
/*	if (tree->arg == templateTree->arg && (templateTree->type != mathNode::Types::VAR || inReplace))
	{
		if (templateTree->arg == "+" || templateTree->arg == "*")
			if (	existEqualSubgraphs(tree->params[0], templateTree->params[0], replace, inReplace) ||
				existEqualSubgraphs(tree->params[1], templateTree->params[1], replace, inReplace) ||
				existEqualSubgraphs(tree->params[1], templateTree->params[0], replace, inReplace) ||
				existEqualSubgraphs(tree->params[0], templateTree->params[1], replace, inReplace))
				return true;
			else
				return false;

		for (int i(0); i < templateTree->params.size(); i++)
			if (!existEqualSubgraphs(tree->params[i], templateTree->params[i], replace, inReplace))
				return false;
		return true;
	}
	else if (templateTree->type == mathNode::Types::VAR && !inReplace)
	{
		bool existReplacement = false;
		for (int i(0); i < replace->size(); i++)
			if (templateTree->arg == replace->at(i).first)
			{
				existReplacement = true;
				return existEqualSubgraphs(tree, replace->at(i).second, replace, true);
			}
		if (!existReplacement)
		{
			replace->push_back(std::pair<std::string, mathNode *>(templateTree->arg, tree));
			return true;
		}
	}

	return false;
*/
}
/*
mathNode *findSubgraph(mathNode *baseGraph, mathNode *templateGraph, typeReplacement &replace)
{
	if (existEqualSubgraphs(baseGraph, templateGraph, replace))
		return baseGraph;
	else
		for (int i(0); i < baseGraph->params.size(); i++)
		{
			mathNode *retRecursion = findSubgraph(baseGraph->params[i], templateGraph, replace);
			if (retRecursion)
				return retRecursion;
		}
	return nullptr;
}

void replace(mathNode *forReplace, mathNode *templateTree, typeReplacement &replace)
{

}
*/
