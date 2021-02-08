#ifndef EXPR_H
#define EXPR_H

#include <vector>
#include <string>
#include <algorithm>

#include "mathNode.h"
#include "../MathSolver.h"

BEG_MATSOLV
USING_MATSOLV

//contain math expression in the form a tree
class Expr
{
public:
	//create and delete
	Expr();
	Expr(std::string);
	Expr(const Expr &);
	~Expr();

	void set(std::string);

	Expr &operator=(const Expr &);

	//returned root node
	mathNode *getTree();

	//erase all memory
	void clear();
	//print tree
	void print(std::ostream & = std::cout, bool = false, bool = false);

	//init values for variables
	void init();
	void init(std::vector<double>);
	//erase values for variables
	void clearValues();

	//calc expression value
	double calc();
	double calc(std::vector<double>);

	Expr replaceRoot(std::string, const Expr &, const Expr &);
	Expr operator==(const Expr &);
	Expr operator+(const Expr &);
	Expr operator-(const Expr &);
	Expr operator*(const Expr &);
	Expr operator/(const Expr &);

	int len(Expr);

	friend Expr copy(const Expr &ref);

private:
	mathNode *root;
	std::vector<std::string> variables;
	std::vector<double> valuesVariables;
	std::vector<char> priorityOperators{'^', '/', '*', '-', '+', '='};

	mathNode *parseNode(std::string);
};

Expr toTree(std::string);

END_MATSOLV

#endif
