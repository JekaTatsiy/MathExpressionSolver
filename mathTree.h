#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class mathTree
{
public:
	struct mathNode
	{
		enum Types
		{
			UNDEF,
			OPER,
			NUM,
			VAR,
			FUNC
		};
		std::string arg;
		Types type;
		std::vector<mathNode *> params;

		mathNode(std::string, Types);
		mathNode(std::string, Types, mathNode *);
		mathNode(std::string, Types, mathNode *, mathNode *);
		~mathNode();

		void addParam(mathNode *);
		double getResult(std::vector<std::string>, std::vector<double>);
	};

	mathNode *root;
	std::vector<std::string> variables;
	std::vector<double> valuesVariables;
	std::vector<std::string> operators{{"^"}, {"*/"}, {"+-"}, {"="}};

	mathNode *parseNode(std::string);
	void printNode(mathNode *, int, std::vector<int> *, std::ostream &, bool);

public:
	mathTree();
	mathTree(std::string);
	mathTree(mathTree &);

	void clear();
	void print(std::ostream & = std::cout, bool = false);

	void init();
	void init(std::vector<double>);
	void clearValues();

	double calc();
	double calc(std::vector<double>);
};