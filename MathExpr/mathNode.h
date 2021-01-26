#ifndef MATH_NODE_H
#define MATH_NODE_H

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include "strAndNum.h"

#define V_LINE 179
#define VE_LINE 192
#define H_LINE 196
#define VL_LINE 195

#define BIG_VAR_LAST [](const mathNode *a, const mathNode *b) -> bool { return isBigVariable(b->arg) ? true : false; }

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
	std::string arg;			  //type action with operands
	Types type;					  //action with operands
	std::list<mathNode *> params; //operands

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
	void print(std::ostream & = std::cout, bool = false, bool = false);

private:
	void printNode(int, std::vector<int> *, std::ostream &, bool, bool);
};

#endif
