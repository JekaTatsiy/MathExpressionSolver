#pragma once

#include <vector>
#include <string>
#include <algorithm>

class mathTree
{
	enum TypesNode
	{
		UNDEF,
		OPER,
		NUM,
		VAR,
		FUNC
	};
	struct mathNode
	{
		std::string arg;
		TypesNode type;
		std::vector<mathNode *> params;
	};

	mathNode *root;

	mathTree();
	mathTree(std::string);
	mathTree(mathTree &newRoot);


	
};