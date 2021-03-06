#include "../mathNode.h"

USING_MATSOLV

mathNode::mathNode(mathNode &node)
{
	arg = node.arg;
	type = node.type;
	for (auto i : node.params)
		addParam(new mathNode(*i));
}

mathNode::mathNode(std::string act, Types tp)
{
	arg = act;
	type = tp;
}

mathNode::mathNode(std::string act, Types tp, mathNode *a)
	: mathNode(act, tp)
{
	params.push_back(a);
}

mathNode::mathNode(std::string act, Types tp, mathNode *a, mathNode *b)
	: mathNode(act, tp)
{
	params.push_back(a);
	params.push_back(b);
}

void mathNode::free()
{
	for (auto i : params)
		if (i)
		{
			i->free();
			i = nullptr;
		}
	delete this;
}

void mathNode::addParam(mathNode *param)
{
	params.push_back(param);
}

//warning: need initialise all variables
double mathNode::getResult(std::vector<std::string> var, std::vector<double> valVar)
{
	if (type == OPER)
	{
		if (arg == "+")
			return (*params.begin())->getResult(var, valVar) + (*(++params.begin()))->getResult(var, valVar);
		if (arg == "-")
			return (*params.begin())->getResult(var, valVar) - (*(++params.begin()))->getResult(var, valVar);
		if (arg == "*")
			return (*params.begin())->getResult(var, valVar) * (*(++params.begin()))->getResult(var, valVar);
		if (arg == "/")
			return (*params.begin())->getResult(var, valVar) / (*(++params.begin()))->getResult(var, valVar);
	}

	if (type == FUNC)
	{
		if (arg == "ln")
			return log((*params.begin())->getResult(var, valVar));
		if (arg == "pow")
			return pow((*params.begin())->getResult(var, valVar), (*(++params.begin()))->getResult(var, valVar));
		if (arg == "abs")
			return abs((*params.begin())->getResult(var, valVar));
		if (arg == "sin")
			return sin((*params.begin())->getResult(var, valVar));
		if (arg == "cos")
			return cos((*params.begin())->getResult(var, valVar));
	}

	if (type == VAR)
		for (size_t i(0); i < var.size(); i++)
			if (var[i] == arg)
				return valVar[i];

	if (type == NUM)
		return toNumber(arg);

	return 0; //undef

	//	return 0.0;
}

void mathNode::print(std::ostream &streamOut, bool showTypeNodes, bool showAdress)
{
	std::vector<int> calledNodes;
	this->printNode(0, &calledNodes, streamOut, showTypeNodes, showAdress);
	std::cout << std::endl;
}

void mathNode::printNode(int layer, std::vector<int> *calledNodes, std::ostream &streamOut, bool showTypeNodes, bool showAdress)
{

	std::vector<int>::iterator del;
	streamOut << arg;
	if (showTypeNodes || type == mathNode::Types::UNDEF)
		streamOut << "  -> " << type;
	if (showAdress)
		streamOut << "(" << this << ")";
	streamOut << std::endl;

	calledNodes->push_back(layer);
	bool f;

	//for (int i(0); i < params.size(); i++)
	for (std::list<mathNode *>::iterator i = params.begin(); i != params.end(); i++)
	{
		for (int j(0); j < layer; j++)
		{
			f = false;
			for (size_t k(0); k < calledNodes->size(); k++)
				if (calledNodes->at(k) == j)
					f = true;
			if (f)
				streamOut << char(LINE_V)
						  << "  ";
			else
				streamOut << " "
						  << "  ";
		}

		streamOut << (*i == *params.rbegin() ? char(LINE_UR) : char(LINE_VR));
		streamOut << char(LINE_H) << char(LINE_H);

		del = std::find(calledNodes->begin(), calledNodes->end(), layer);
		if (*i == *params.rbegin() && del != calledNodes->end())
			calledNodes->erase(del);

		(*i)->printNode(layer + 1, calledNodes, streamOut, showTypeNodes, showAdress);
	}
	del = std::find(calledNodes->begin(), calledNodes->end(), layer);
	if (del != calledNodes->end())
		calledNodes->erase(del);
}
