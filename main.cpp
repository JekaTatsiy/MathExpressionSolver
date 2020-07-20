#include <iostream>
#include <string>
#include "mathTree.h"
#include "strAndNum.h"
#include "comparisonOfTree.h"

using namespace std;

int main()
{


	mathTree a("1+x^2-9");
	mathTree b("(r^2)*(cos(2*x)+sin(2*x)*i)");
	//mathTree b("A-B");

	a.print();
	b.print();

	/*
	typeReplacement *currentReplacement = new typeReplacement;

	//cout << equalGraphs(a.getTree(), b.getTree(), currentReplacement) << endl;
	cout << findSubgraph(a.getTree(), b.getTree(), currentReplacement) << endl;
	for (auto i : *currentReplacement)
	{
		cout << "variables: " << i.first << endl
			 << "equal:" << endl;
		i.second->print();
		cout << endl;
	}
*/
	return 0;
}