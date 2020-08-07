#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "../mathExpr.h"

using namespace std;

int main()
{
	vector<string> dataExpr = {"x+y",	"a+b+c",	"a*(b+c)",	"(a+b)/(c-d)",	"a*(b+c)",	"a+(b-c^2)"};
	vector<string> dataTmpl = {"A+B",	"A-B",		"A*B",		"A/B",		"A+B",		"A^2"};	
	vector<bool> ans = {true,false,true,true,true,true};
	vector<bool> myAns;
	int cntQ = ans.size();
	int cntCorrectA = 0;
		
	mathTree expr;
	mathTree tmpl;


	for (int i = 0; i < ans.size(); i++)
	{
		expr.set(dataExpr[i]);
		tmpl.set(dataTmpl[i]);
		myAns.push_back(bool(existEqualSubgraph(expr.getTree(),tmpl.getTree())) == ans[i]);
		cntCorrectA += myAns[i]==ans[i];
	}
	cout << "test \"find subgraph\" done: " << cntCorrectA << "/" << cntQ << "  " << setw(2) << float(cntCorrectA) / float(cntQ)* 100.0 << "%" << endl; 
	for(int i=0;i<myAns.size();i++)
		cout << myAns[i]<<" ";
	cout << endl;

	return 0;
}

