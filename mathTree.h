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

		mathNode(std::string act, TypesNode type);
		mathNode(std::string act, TypesNode type, mathNode *a);
		mathNode(std::string act, TypesNode type, mathNode *a, mathNode *b);
		~mathNode();
	};

	mathNode *root;
	std::vector<std::string> variables;
	std::vector<double> valuesVariables;

public:
	mathTree();
	mathTree(std::string);
	mathTree(mathTree &newRoot);
};