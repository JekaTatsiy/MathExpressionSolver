#include "mathTree.h"
#include "strAndNum.h"

mathTree::mathTree()
{
	root = nullptr;
}

mathTree::mathTree(std::string expression)
{
	root = parseNode(delBrackets(expression));
}

mathTree::mathNode *mathTree::parseNode(std::string expression)
{
	for (auto it = operators.end() - 1; it >= operators.begin(); it--)
		for (size_t i(0); i < expression.size(); i++)
			if (std::search(it->begin(), it->end(), expression.begin() + i, expression.begin() + i + 1) != it->end() && !inBrackets(expression, i))
				if (it != operators.begin()) //из-за некоторые проблемы с '^' в консоле
					return new mathNode(
						std::string(1, *(expression.begin() + 1)),
						OPER,
						parseNode(delBrackets(std::string(expression.begin(), expression.begin() + i))),
						parseNode(delBrackets(std::string(expression.begin() + i + 1, expression.end()))));
				else
					return new mathNode(
						"pow",
						FUNC,
						parseNode(delBrackets(std::string(expression.begin(), expression.begin() + i))),
						parseNode(delBrackets(std::string(expression.begin() + i + 1, expression.end()))));

	if (isNumber(expression))
		return new mathNode(expression, NUM);

	if (isVariable(expression))
	{
		variables.push_back(expression);
		return new mathNode(expression, VAR);
	}

	if (isfunction(expression))
	{
		std::string::iterator startScan = std::find(expression.begin(), expression.end(), '(');
		int openBrackets = 0;

		mathNode *funcNode = new mathNode(std::string(expression.begin(), startScan), FUNC);

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

	return new mathNode(expression, UNDEF); //undefine
}

/*mathTree::mathTree(mathTree &newRoot)
{
}*/

//========================  mathTree::mathNode  ============================

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
	delete this;
}

void mathTree::mathNode::addParam(mathNode *param)
{
	params.push_back(param);
}
