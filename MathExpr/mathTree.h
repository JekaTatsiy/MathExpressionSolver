#ifndef MATH_TREE_H
#define MATH_TREE_H

#include <vector>
#include <string>
#include <algorithm>

#include "mathNode.h"

//contain math expression in the form a tree
class mathTree
{
public:
	//create and delete
	mathTree();
	mathTree(std::string);
	mathTree(const mathTree &);
	~mathTree();

	void set(std::string);

	mathTree &operator=(const mathTree &);

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

	mathTree replaceRoot(std::string, const mathTree &, const mathTree &);
	mathTree operator==(const mathTree &);
	mathTree operator+(const mathTree &);
	mathTree operator-(const mathTree &);
	mathTree operator*(const mathTree &);
	mathTree operator/(const mathTree &);

	friend mathTree copy(const mathTree &ref);

private:
	mathNode *root;
	std::vector<std::string> variables;
	std::vector<double> valuesVariables;
	std::vector<char> priorityOperators{'^', '/', '*', '-', '+', '='};

	mathNode *parseNode(std::string);
};

mathTree toTree(std::string);

#endif
