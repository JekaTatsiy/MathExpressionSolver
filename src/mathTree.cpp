#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

#include "../mathNode.h"
#include "../mathTree.h"
#include "../strAndNum.h"

mathTree::mathTree()
{
	root = nullptr;
}

mathTree::mathTree(std::string expression):mathTree()
{
	set(expression);
}

mathTree::mathTree(mathTree &tree)
{
	variables = tree.variables;
	valuesVariables = tree.valuesVariables;
	root = new mathNode(*tree.root);
}

mathTree::~mathTree()
{
	if(root!=nullptr)
		clear();
}

void mathTree::set(std::string expression)
{
	if(root!=nullptr)
		delete root;
	root = parseNode(delBrackets(expression));
}

mathNode *mathTree::getTree()
{
	return root;
}

mathNode *mathTree::parseNode(std::string expression)
{
	for (auto it = priorityOperators.end() - 1; it >= priorityOperators.begin(); it--)
		for (size_t i(0); i < expression.size(); i++)
			if (expression[i] == *it && !inBrackets(expression, i))
				if (it != priorityOperators.begin())
					return new mathNode(
						std::string(1, *(expression.begin() + i)),
						mathNode::Types::OPER,
						parseNode(delBrackets(std::string(expression.begin(), expression.begin() + i))),
						parseNode(delBrackets(std::string(expression.begin() + i + 1, expression.end()))));
				else
					return new mathNode(
						"pow",
						mathNode::Types::FUNC,
						parseNode(delBrackets(std::string(expression.begin(), expression.begin() + i))),
						parseNode(delBrackets(std::string(expression.begin() + i + 1, expression.end()))));

	if (isNumber(expression))
		return new mathNode(expression, mathNode::Types::NUM);

	if (isVariable(expression))
	{
		variables.push_back(expression);
		return new mathNode(expression, mathNode::Types::VAR);
	}

	if (isfunction(expression))
	{
		std::string::iterator startScan = std::find(expression.begin(), expression.end(), '(');
		int openBrackets = 0;

		mathNode *funcNode = new mathNode(std::string(expression.begin(), startScan), mathNode::Types::FUNC);

		for (auto i = startScan; i != expression.end(); i++)
		{
			if (*i == '(')
				openBrackets++;
			else if (*i == ')')
				openBrackets--;

			if ((*i == ',' && openBrackets == 1) || openBrackets == 0)
			{
				funcNode->addParam(parseNode(delBrackets(std::string(startScan + 1, i))));
				startScan = i;
			}
		}

		return funcNode;
	}

	return new mathNode(expression, mathNode::Types::UNDEF); //undefine
}

void mathTree::clear()
{
	variables.clear();
	valuesVariables.clear();
	root->free();
}

void mathTree::print(std::ostream &streamOut, bool showTypeNodes)
{
	if(root!=nullptr)
	{
		std::vector<int> calledNodes;
		root->print(streamOut, showTypeNodes);
		streamOut << std::endl;
	}else
		streamOut << "no expression"<<std::endl;

}
void mathTree::init()
{
	double inputValues;
	std::cout << "input values:" << std::endl;
	for (size_t i(0); i < variables.size(); i++)
	{
		std::cout << variables[i] << ": ";
		std::cin >> inputValues;
		valuesVariables.push_back(inputValues);
	}
}
void mathTree::init(std::vector<double> val)
{
	if (val.size() == variables.size())
		valuesVariables = val;
}
void mathTree::clearValues()
{
	valuesVariables.clear();
}

double mathTree::calc()
{
	return root->getResult(variables, valuesVariables);
}
double mathTree::calc(std::vector<double> val)
{
	init(val);
	double res = calc();
	clearValues();
	return res;
}
