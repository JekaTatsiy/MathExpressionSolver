#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

//contain math expression in the form a tree
class mathTree
{
public:
	//contain one math expression
	struct mathNode
	{
		//describes what the stuct type action with operands
		enum Types
		{
			UNDEF,
			OPER,
			NUM,
			VAR,
			FUNC
		};

		std::string arg;//type action with operands
		Types type;//action with operands
		std::vector<mathNode *> params;//operands

		mathNode(mathNode &);
		mathNode(std::string, Types);
		mathNode(std::string, Types, mathNode *);
		mathNode(std::string, Types, mathNode *, mathNode *);
		void free();

		//add new param(for functions)
		void addParam(mathNode *);
		//calc result
		double getResult(std::vector<std::string>, std::vector<double>);
		//print yourself
		void print(std::ostream & = std::cout, bool = false);

	private:
		void printNode(int, std::vector<int> *, std::ostream &, bool);
	};

	//create and delete
	mathTree();
	mathTree(std::string);
	mathTree(mathTree &);//не правильно
	~mathTree();

	//returned root node
	mathNode *getTree();

	//erase all memory
	void clear();
	//print tree
	void print(std::ostream & = std::cout, bool = false);

	//init values for variables
	void init();
	void init(std::vector<double>);
	//erase values for variables
	void clearValues();

	//calc expression value
	double calc();
	double calc(std::vector<double>);

private:
	mathNode *root;
	std::vector<std::string> variables;
	std::vector<double> valuesVariables;
	std::vector<char> priorityOperators{'^', '/', '*', '-', '+', '='};

	mathNode *parseNode(std::string);
};
