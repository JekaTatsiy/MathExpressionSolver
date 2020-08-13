#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "../mathExpr.h"

using namespace std;

int main()
{
	cout << "test \"find subgraph\" ";

	vector<string> dataExpr = 
	{"x+y",	"a+b+c",	"a*(b+c)",	"(a+b)/(c-d)",	"a*(b+c)",	"a+(b-c^2)",	"1+2+3+x",	"1+2+3+x",	"x^3+x^2+x+1",	"x^3+x^2+x+1",	"sin(x)+y",	"y+1"};
	vector<string> dataTmpl = 
	{"A+B",	"A-B",		"A*B",		"A/B",			"A+B",		"A^2",			"1+A",		"2+x",		"A^2+1",		"x^3+1",		"A+sin(B)",	"x+1"};	
	vector<bool> ans = {true,false,true,true,true,true,true,true,true,true,true,false};
	vector<bool> myAns;
	int cntQ = ans.size();
	int cntCorrectA = 0;
		
	if(dataExpr.size() != dataTmpl.size() && dataExpr.size() != ans.size())
	{
		cout << "error: count Q != A"<<endl;
		return 0;
	}

	mathTree expr;
	mathTree tmpl;


	for (int i = 0; i < ans.size(); i++)
	{
		expr.set(dataExpr[i]);
		tmpl.set(dataTmpl[i]);
		myAns.push_back(bool(existEqualSubgraph(expr.getTree(),tmpl.getTree())) == ans[i]);
		cntCorrectA += myAns[i]==ans[i];
	}
	cout << "done: " << cntCorrectA << "/" << cntQ << "  " << setw(2) << float(cntCorrectA) / float(cntQ)* 100.0 << "%" << endl; 
	if(cntCorrectA != cntQ)
	{
		for(int i=0;i<myAns.size();i++)
			cout << (myAns[i] == ans[i]) << " ";		
		cout << endl;

		for(int i=0;i<myAns.size();i++)
			if(myAns[i]!=ans[i])
				cout << "{" << dataExpr[i] << ", " << dataTmpl[i] << ", " << ans[i] << "}" << endl;
		cout << endl;
	}

	return 0;
}

