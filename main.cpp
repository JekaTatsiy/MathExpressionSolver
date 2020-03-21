#include <iostream>
#include <string>
#include "mathTree.h"
#include "strAndNum.h"
#include "comparisonOfTree.h"

using namespace std;

int main()
{
	mathTree a("x^2-9");
	mathTree b("A-B");
	typeReplacement *currentReplacement = new typeReplacement;

	a.print();
	a.getTree()->print();
	/*
	cout << equal(a.getTree(), b.getTree(), currentReplacement);
	for (auto i : *currentReplacement)
	{
		cout << "variables: " << i.first << endl
			 << "equal:" << endl;
		i.second->printNode()

	}*/

	return 0;
}