#include "../comparisonOfTree.h"

USING_MATSOLV

void typeReplace::addEqual(std::string templ, mathNode* node)
{
	replacePattern::iterator iterIns = repl.begin();
	for(; iterIns != repl.end(); iterIns++)
	{
		if(iterIns->first==templ)
		{
			iterIns->second.push_back(node);
			return;	
		}
	}
	repl.push_back(std::pair <std::string, std::vector<mathNode*>>(templ,std::vector<mathNode*>{node})); 
	return;	
}

void typeReplace::print()
{
	std::cout << "replace: " << std::endl;
	if(repl.size()==0)
		std::cout << "\treplace is empty" << std::endl;
	for(auto i: repl)
	{
		std::cout << i.first << std::endl;
		for(auto j: i.second)
			j->print();
	}

}

mathNode* MATSOLV::existEqualSubgraph(mathNode *tree, mathNode *templ, typeReplace &curReplace, char flags)
{
	if (templ->type==mathNode::Types::VAR && isBigVariable(templ->arg)) //tree оказался подходящим для шаблона templ
	{
		curReplace.addEqual(templ->arg,tree);
		return tree;
	}
	else if(tree->arg == "+" || tree->arg == "*") //комутативная операция
	{		
		 
		if(tree->arg==templ->arg)
		{
			std::list<mathNode*> treeCommutative  = getCommutativeOperands(tree, tree->arg);
			std::list<mathNode*> templCommutative = getCommutativeOperands(templ, tree->arg);
			for(auto templParams: templCommutative)
			{
				bool existEqual=false;
				for(auto treeParams: treeCommutative)
					if (existEqualSubgraph(treeParams, templParams, curReplace, WAS_COLLISION))
						existEqual=true;
				if(!existEqual)
					return nullptr;	
			}
			return tree;
		}
		else
		{
			bool existEqual=false;
			for(auto treeParamsIter: tree->params)
			{
				if (existEqualSubgraph(treeParamsIter,templ,curReplace,flags))
				{
					existEqual=true;
					if(templ->type!=mathNode::VAR)
						break;
				}
			}
			if(!existEqual)
				return nullptr;	
			else
				return tree;
		}
	}		
	else if(tree->arg == templ->arg && tree->params.size()==templ->params.size()) //совпали операции и количество операндов
	{
		if(flags & WAS_COLLISION) //при необходимости совпадения сейчас
		{
			mathNode* equal;
			for(auto i: tree->params)
				equal = existEqualSubgraph(i,templ,curReplace, WAS_COLLISION);
					if(equal)
						return equal;		
		}
		std::list<mathNode*>::iterator treeParam = tree->params.begin();
		std::list<mathNode*>::iterator templParam = templ->params.begin();
		std::list<mathNode*> templIsPattern;
		std::list<mathNode*> treeWhenTemplIsPattern;

		for(int i=0;i<tree->params.size();i++, treeParam++, templParam++)//corresponding operands are equaivalent
			if(isBigVariable((*templParam)->arg))
			{
				templIsPattern.push_back(*templParam);
				treeWhenTemplIsPattern.push_back(*treeParam);
			}
			else if(!existEqualSubgraph(*treeParam, *templParam, curReplace, WAS_COLLISION))
				return nullptr;
		
		treeParam=treeWhenTemplIsPattern.begin();
		templParam=templIsPattern.begin();
		
		for(;treeParam!=treeWhenTemplIsPattern.end(); treeParam++, templParam++)//corresponding operands are equaivalent
			if(!existEqualSubgraph(*treeParam, *templParam, curReplace, WAS_COLLISION))
				return nullptr;

		return tree;
	}
	else if(!flags & WAS_COLLISION) //нет совпадения
	{	
		for(auto treeIter: tree->params)
			if(existEqualSubgraph(treeIter,templ,curReplace))
				return tree;
	}	
	return nullptr;
}	

std::list<mathNode*> MATSOLV::getCommutativeOperands(mathNode* tree, std::string oper)
{
	std::list<mathNode*> res;
	for(auto param: tree->params)
	{
		if(param->arg!=oper)
			res.push_back(param);
		else
			res.merge(getCommutativeOperands(param,oper));
	}
	res.sort(BIG_VAR_LAST);
	return res;
}



void replace(mathNode *forReplace, mathNode *templateTree, typeReplace &replace)
{

}




