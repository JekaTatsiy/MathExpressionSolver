#include "mathTree.h"

mathTree::mathTree()
{
	root = nullptr;
}






mathTree::mathNode::mathNode(std::string act, TypesNode type)
{
	arg = act;
	type = type;
}

mathTree::mathNode::mathNode(std::string act, TypesNode type, mathNode *a)
{
	arg = act;
	type = type;
	params.push_back(a);
}

mathTree::mathNode::mathNode(std::string act, TypesNode type, mathNode *a, mathNode *b)
{
	arg = act;
	type = type;
	params.push_back(a);
	params.push_back(b);
}

mathTree::mathNode::~mathNode() //возможно работает неправильно
{
	for (auto i : params)
		delete i;
}