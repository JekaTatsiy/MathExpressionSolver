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

	cout << equalGraphs(a.getTree(), b.getTree(), currentReplacement) << endl;
	for (auto i : *currentReplacement)
	{
		cout << "variables: " << i.first << endl
			 << "equal:" << endl;
		i.second->print();
		cout << endl;
	}

	return 0;
}