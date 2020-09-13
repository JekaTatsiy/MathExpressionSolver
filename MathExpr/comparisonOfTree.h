#ifndef COMPARISON_OF_TREE_H
#define COMPARISON_OF_TREE_H

#include "mathNode.h"
#include "mathTree.h"
#include "strAndNum.h"
#include <list>
#include <string>

#define NOTHING 		char(0x00)
#define WAS_COLLISION 	char(0x01) //гарантирует что предыдущие узлы совпали
#define WAS_COMMUTATIVE	char(0x02) //гарантирует что предыдущая операция была комутативна

struct typeReplace
{
	typedef	std::vector<std::pair<std::string, std::vector<mathNode *>>> replacePattern;
	std::vector<std::pair<std::string, std::vector<mathNode *>>> repl;
	typeReplace(){};

	void addEqual(std::string, mathNode*);
	void print();
	void clear(){repl.erase(repl.begin(),repl.end());}
};

mathNode* existEqualSubgraph(mathNode *, mathNode *, typeReplace&, char = NOTHING);

std::list<mathNode*> getCommutativeOperands(mathNode*, std::string);

void replace(mathNode *, mathNode *, typeReplace *);

#endif

