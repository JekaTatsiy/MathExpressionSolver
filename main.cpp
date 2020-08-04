#include <iostream>
#include <string>
#include "mathExprSlvr.h"

using namespace std;

int main(int argc,char**argv)
{
	
	mathTree a("1+x^2-9");
	a.print();
	mathTree b("(r^2)*(cos(2*x)+sin(2*x)*i)");
	b.print();
	mathTree c("A-B");
	c.print();


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
