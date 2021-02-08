#include "../Expr.h"


USING_MATSOLV


Expr::Expr()
{
	root = nullptr;
}

Expr::Expr(std::string expression) : Expr()
{
	set(expression);
}

Expr::Expr(const Expr &tree)
{
	variables = tree.variables;
	valuesVariables = tree.valuesVariables;
	root = new mathNode(*tree.root);
}

Expr::~Expr()
{
	if (root)
		clear();
}

Expr &Expr::operator=(const Expr &tree)
{
	clear();
	root = new mathNode(*tree.root);
	return *this;
}

void Expr::set(std::string expression)
{
	if (root)
		delete root;
	if (expression.size() != 0)
		root = parseNode(delBrackets(expression));
}

mathNode *Expr::getTree()
{
	return root;
}

void Expr::clear()
{
	variables.clear();
	valuesVariables.clear();
	if (root)
		root->free();
	root = nullptr;
}

void Expr::print(std::ostream &streamOut, bool showTypeNodes, bool showAdress)
{
	if (root)
	{
		std::vector<int> calledNodes;
		root->print(streamOut, showTypeNodes,showAdress);
		streamOut << std::endl;
	}
	else
		streamOut << "no expression" << std::endl;
}
void Expr::init()
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
void Expr::init(std::vector<double> val)
{
	if (val.size() == variables.size())
		valuesVariables = val;
}
void Expr::clearValues()
{
	valuesVariables.clear();
}

double Expr::calc()
{
	return root->getResult(variables, valuesVariables);
}
double Expr::calc(std::vector<double> val)
{
	init(val);
	double res = calc();
	clearValues();
	return res;
}

Expr Expr::replaceRoot(std::string act, const Expr &l, const Expr &r)
{
	mathNode::Types tp;
	if (act == "=" || act == "+" || act == "-" || act == "*" || act == "/")
		tp = mathNode::Types::OPER;
	if (isFunction(act))
		tp = mathNode::Types::FUNC;
	if (isNumber(act))
		tp = mathNode::Types::NUM;
	if (isVariable(act))
		tp = mathNode::Types::VAR;

	root = new mathNode(act, tp, l.root, r.root);
	return *this;
}

Expr Expr::operator==(const Expr &r)
{
	return replaceRoot("=", *this, copy(r));
}

Expr Expr::operator+(const Expr &r)
{
	return replaceRoot("+", *this, copy(r));
}

Expr Expr::operator-(const Expr &r)
{
	return replaceRoot("-", *this, copy(r));
}

Expr Expr::operator*(const Expr &r)
{
	return replaceRoot("*", *this, copy(r));
}

Expr Expr::operator/(const Expr &r)
{
	return replaceRoot("/", *this, copy(r));
}

int Expr::len(Expr v)
{
	return 1;
}


mathNode *Expr::parseNode(std::string expression)
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

	if (isFunction(expression))
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

BEG_MATSOLV

Expr copy(const Expr &ref)
{
	return Expr(ref);
}

Expr toTree(std::string arg)
{
	return Expr(arg);
}

END_MATSOLV
