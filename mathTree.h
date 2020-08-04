#ifndef MATH_TREE_H
#define MATH_TREE_H

#include <vector>


//contain math expression in the form a tree
class mathTree
{
public:
	//create and delete
	mathTree();
	mathTree(std::string);
	mathTree(mathTree &);
	~mathTree();
	
	void set(std::string);

	//returned root node
	mathNode *getTree();

	//erase all memory
	void clear();
	//print tree
	void print(std::ostream & = std::cout, bool = false);

	//init values for variables
	void init();
	void init(std::vector<double>);
	//erase values for variables
	void clearValues();

	//calc expression value
	double calc();
	double calc(std::vector<double>);

private:
	mathNode *root;
	std::vector<std::string> variables;
	std::vector<double> valuesVariables;
	std::vector<char> priorityOperators{'^', '/', '*', '-', '+', '='};

	mathNode *parseNode(std::string);
};

#endif
