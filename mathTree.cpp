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

void mathTree::printNode(mathTree::mathNode *node, int layer, std::vector<int> *calledNodes, std::ostream &streamOut, bool showTypeNodes)
{
	std::vector<int>::iterator del;
	streamOut << node->arg;
	if (showTypeNodes || node->type == mathNode::Types::UNDEF)
		streamOut << "  -> " << node->type;
	streamOut << std::endl;

	calledNodes->push_back(layer);
	bool f;

	for (int i(0); i < node->params.size(); i++)
	{
		for (int j(0); j < layer; j++)
		{
			f = false;
			for (size_t k(0); k < calledNodes->size(); k++)
				if (calledNodes->at(k) == j)
					f = true;
			if (f)
				streamOut << char(179) << "   ";
			else
				streamOut << char(32) << "   ";
		}

		streamOut << (i == (node->params.size() - 1) ? char(192) : char(195));
		for (int j(0); j < 3; j++)
			streamOut << char(196);

		del = std::find(calledNodes->begin(), calledNodes->end(), layer);
		if (i == node->params.size() - 1 && del != calledNodes->end())
			calledNodes->erase(del);

		printNode(node->params[i], layer + 1, calledNodes, streamOut, showTypeNodes);
	}
	del = std::find(calledNodes->begin(), calledNodes->end(), layer);
	if (del != calledNodes->end())
		calledNodes->erase(del);
}

void mathTree::print(std::ostream &streamOut, bool showTypeNodes)
{
	std::vector<int> calledNodes;
	printNode(root, 0, &calledNodes, streamOut, showTypeNodes);
	std::cout << std::endl;
}

/*mathTree::mathTree(mathTree &newRoot)
{
}*/

//========================  mathTree::mathNode  ============================

mathTree::mathNode::mathNode(std::string act, Types tp)
{
	arg = act;
	type = tp;
}

mathTree::mathNode::mathNode(std::string act, Types tp, mathNode *a)
{
	arg = act;
	type = tp;
	params.push_back(a);
}

mathTree::mathNode::mathNode(std::string act, Types tp, mathNode *a, mathNode *b)
{
	arg = act;
	type = tp;
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
