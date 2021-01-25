#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "../MathExpr/mathExpr.h"

using namespace std;

int main()
{
	cout << "test \"find subgraph\" ";

	vector<string> dataExpr = 
	{"x+y",	"a+b",	"a-b",	"a+b+c",	"a*(b+c)",	"a*(b+c)",	"(a+b)/(c-d)",		"a+(b-c^2)",	"1+2+3+x",	"1+2+3+x",	"x^3+z+1",	"x^3+y^2+z+1",	"x^3+y^2+z+1",	"x^3+y^2+z+1",	"x^3+y^2+z+1",	"sin(x)+y",	"y+1",	"y+1",	"y+1",	"pow(x,2)"};
	vector<string> dataTmpl = 
	{"A+B",	"A-B",	"a+b",	"A-B",		"A*B",		"A+B",		"A/B",				"A^2",			"1+A",		"2+x",		"A^2+1",		"x^3+1",		"A^3+B^2+1",	"A^2+1+B^3",	"y^2+1+x^3",	"A+sin(B)",	"x+1",	"1+y",	"1+A",	"pow(2,x)"};	
	vector<bool> ans = 
	{true,	false,	false,	false,		true,		true,		true,				true,			true,		true,		false,			true,			true,			true,			true,			true,		false,	true,	true,	false};
	
	vector<bool> myAns;
	int cntQ = ans.size();
	int cntCorrectA = 0;
		
	if(dataExpr.size() != dataTmpl.size() || dataExpr.size() != ans.size())
	{
		cout << "error: count Q != A"<<endl;
		return 0;
	}

	mathTree expr;
	mathTree tmpl;
	typeReplace repl;
	mathNode *curAns;

	for (int i = 0; i < ans.size(); i++)
	{
		expr.set(dataExpr[i]);
		tmpl.set(dataTmpl[i]);
		curAns = existEqualSubgraph(expr.getTree(),tmpl.getTree(),repl);
		myAns.push_back(curAns==nullptr?false:true);
		cntCorrectA += (myAns[i]==ans[i]);
		

		cout << endl << "{" << dataExpr[i] << ", " << dataTmpl[i] << "}"<<endl;
		repl.print();
		repl.clear();

	}
	cout << "done" << endl; 
	if(cntCorrectA != cntQ)
	{
		for(int i=0;i<myAns.size();i++)
			cout << (myAns[i] == ans[i]?'+':'-') << " ";		
		cout << endl;

		for(int i=0;i<myAns.size();i++)
			if(myAns[i]!=ans[i])
				cout << "{" << dataExpr[i] << ", " << dataTmpl[i] << ", " << "cor: "<<ans[i] << "  my: " << myAns[i] << "}" << endl;
		cout << endl;
	}

	return 0;
}

