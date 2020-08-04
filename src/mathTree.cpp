
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

mathTree::mathNode *mathTree::getTree()
{
	return root;
}

mathTree::mathNode *mathTree::parseNode(std::string expression)
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

//========================  mathTree::mathNode  ============================

mathTree::mathNode::mathNode(mathTree::mathNode &node)
{
	arg = node.arg;
	type = node.type;
	for (auto i : node.params)
		addParam(new mathNode(*i));
}

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

void mathTree::mathNode::free()
{
	for (auto i : params)
		if (i)
			i->free();
	delete this;
}

void mathTree::mathNode::addParam(mathNode *param)
{
	params.push_back(param);
}

double mathTree::mathNode::getResult(std::vector<std::string> var, std::vector<double> valVar)
{
	if (this->type == OPER)
	{
		if (arg == "+")
			return params[0]->getResult(var, valVar) + params[1]->getResult(var, valVar);
		if (arg == "-")
			return params[0]->getResult(var, valVar) - params[1]->getResult(var, valVar);
		if (arg == "*")
			return params[0]->getResult(var, valVar) * params[1]->getResult(var, valVar);
		if (arg == "/")
			return params[0]->getResult(var, valVar) / params[1]->getResult(var, valVar);
	}

	if (type == FUNC)
	{
		if (arg == "ln")
			return log(params[0]->getResult(var, valVar));
		if (arg == "pow")
			return pow(params[0]->getResult(var, valVar), params[1]->getResult(var, valVar));
		if (arg == "abs")
			return abs(params[0]->getResult(var, valVar));
		if (arg == "sin")
			return sin(params[0]->getResult(var, valVar));
		if (arg == "cos")
			return cos(params[0]->getResult(var, valVar));
	}

	if (type == VAR)
		for (size_t i(0); i < var.size(); i++)
			if (var[i] == arg)
				return valVar[i];

	if (type == NUM)
		return toNumber(arg);

	return 0; //undef
}

void mathTree::mathNode::print(std::ostream &streamOut, bool showTypeNodes)
{
	std::vector<int> calledNodes;
	this->printNode(0, &calledNodes, streamOut, showTypeNodes);
	std::cout << std::endl;
}

void mathTree::mathNode::printNode(int layer, std::vector<int> *calledNodes, std::ostream &streamOut, bool showTypeNodes)
{
	std::vector<int>::iterator del;
	streamOut << arg;
	if (showTypeNodes || type == mathNode::Types::UNDEF)
		streamOut << "  -> " << type;
	streamOut << std::endl;

	calledNodes->push_back(layer);
	bool f;

	for (int i(0); i < params.size(); i++)
	{
		for (int j(0); j < layer; j++)
		{
			f = false;
			for (size_t k(0); k < calledNodes->size(); k++)
				if (calledNodes->at(k) == j)
					f = true;
			if (f)
				streamOut << "│" << "   ";
			else
				streamOut << " " << "   ";
		}

		streamOut << (i == (params.size() - 1) ? "└" : "├" );
		for (int j(0); j < 3; j++)
			streamOut << "─";

		del = std::find(calledNodes->begin(), calledNodes->end(), layer);
		if (i == params.size() - 1 && del != calledNodes->end())
			calledNodes->erase(del);

		params[i]->printNode(layer + 1, calledNodes, streamOut, showTypeNodes);
	}
	del = std::find(calledNodes->begin(), calledNodes->end(), layer);
	if (del != calledNodes->end())
		calledNodes->erase(del);
}
