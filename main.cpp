#include <iostream>
#include <string>
#include "mathTree.h"

using namespace std;

int main(int argc,char**argv)
{

	mathTree a("a+b*(r^2)/3");
	mathTree b("A+B");
	a.print();
	b.print();
//	b=a;
//	b.print();

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
