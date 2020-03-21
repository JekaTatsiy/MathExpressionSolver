#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class mathTree
{
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

		mathNode(mathNode &);
		mathNode(std::string, Types);
		mathNode(std::string, Types, mathNode *);
		mathNode(std::string, Types, mathNode *, mathNode *);
		void free();

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
//create and delete
	mathTree();
	mathTree(std::string);
	mathTree(mathTree &);
	~mathTree();

//erase all memory
	void clear();
//print tree 
	void print(std::ostream & = std::cout, bool = false);

//init values for variables
	void init();
	void init(std::vector<double>);
//erase valuse for variables
	void clearValues();

//calc expression value
	double calc();
	double calc(std::vector<double>);





};