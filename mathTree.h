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

		mathNode(std::string, TypesNode);
		mathNode(std::string, TypesNode, mathNode *);
		mathNode(std::string, TypesNode, mathNode *, mathNode *);
		~mathNode();

		void clear();
		void addParam(mathNode *);
	};

	mathNode *root;
	std::vector<std::string> variables;
	std::vector<double> valuesVariables;
	std::vector<std::string> operators{{"^"}, {"*/"}, {"+-"}, {"="}};

	mathNode *parseNode(std::string);

public:
	mathTree();
	mathTree(std::string);
	mathTree(mathTree &);
};