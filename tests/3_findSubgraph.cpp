#include <iostream>
#include <vector>
#include <string.h>
#include <iomanip>

#include "../Expr/Expr.h"
#include "../ExprReplace/comparisonOfTree.h"
#include "../MathSolver.h"

using namespace std;
using namespace mathSolver;

int main(int argc, char **argv)
{
	bool view = false;
	for (int i = 0; i < argc; i++)
		if ((strcmp(argv[i],"-V")==0) || (strcmp(argv[i], "view")==0))
			view = true;

	cout << "test \"find subgraph\" " << endl;

	vector<string> dataExpr =
		{"x+y", "a+b", "a-b", "a+b+c", "a*(b+c)", "a*(b+c)", "(a+b)/(c-d)", "a+(b-c^2)", "1+2+3+x", "1+2+3+x", "x^3+z+1", "x^3+y^2+z+1", "x^3+y^2+z+1", "x^3+y^2+z+1", "x^3+y^2+z+1", "sin(x)+y", "y+1", "y+1", "y+1", "pow(x,2)"};
	vector<string> dataTmpl =
		{"A+B", "A-B", "a+b", "A-B", "A*B", "A+B", "A/B", "A^2", "1+A", "2+x", "A^2+1", "x^3+1", "A^3+B^2+1", "A^2+1+B^3", "y^2+1+x^3", "A+sin(B)", "x+1", "1+y", "1+A", "pow(2,x)"};
	vector<bool> ans =
		{true, false, false, false, true, true, true, true, true, true, false, true, true, true, true, true, false, true, true, false};

	vector<bool> myAns;
	int cntQ = ans.size();
	int cntCorrectA = 0;

	if (dataExpr.size() != dataTmpl.size() || dataExpr.size() != ans.size())
	{
		cout << "error: count Q != A" << endl;
		return 0;
	}

	Expr expr;
	Expr tmpl;
	typeReplace repl;
	mathNode *curAns;

	for (int i = 0; i < ans.size(); i++)
	{
		expr.set(dataExpr[i]);
		tmpl.set(dataTmpl[i]);
		curAns = existEqualSubgraph(expr.getTree(), tmpl.getTree(), repl);
		myAns.push_back(curAns == nullptr ? false : true);
		cntCorrectA += (myAns[i] == ans[i]);

		if (view)
		{
			cout << endl
				 << "{" << dataExpr[i] << ", " << dataTmpl[i] << "}" << endl;
			repl.print();
		}
		repl.clear();
	}

	if (view)
		if (cntCorrectA != cntQ)
		{
			for (int i = 0; i < myAns.size(); i++)
				cout << (myAns[i] == ans[i] ? '+' : '-') << " ";
			cout << endl;

			for (int i = 0; i < myAns.size(); i++)
				if (myAns[i] != ans[i])
					cout << "{" << dataExpr[i] << ", " << dataTmpl[i] << ", "
						 << "cor: " << ans[i] << "  my: " << myAns[i] << "}" << endl;
			cout << endl;
		}
		
	cout << "\tdone." << endl;

	return 0;
}
