#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

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
	void printNode(mathNode *node, int layer, std::vector<int> *calledNodes, std::ostream &streamOut, bool showTypeNodes);

public:
	mathTree();
	mathTree(std::string);
	mathTree(mathTree &);

	void print(std::ostream &streamOut = std::cout, bool showTypeNodes = false);
};