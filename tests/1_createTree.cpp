#include <iostream>
#include <vector>
#include <string.h>
#include <iomanip>

#include "../MathExpr/mathExpr.h"

using namespace std;

int main(int argc, char **argv)
{
	bool view = false;
	for (int i = 0; i < argc; i++)
		if ((strcmp(argv[i],"-V")==0) || (strcmp(argv[i], "view")==0))
			view = true;

	cout << "test \"create tree\": " << endl;

	vector<string> inputData =
		{"", "a", "x+y", "a+b+c", "a*(b+c)", "a*b+c", "(a+b)/(c-d)", "a+(b*c^2)",
		 "1+2+3+x", "1+2+3+x", "sin(a^2)^(1/2)", "log(2,e)"};

	mathTree testTree;
	for (auto i : inputData)
	{
		testTree.set(i);
		if (view)
		{
			cout << i << endl;
			testTree.print();
			cout << endl;
		}
		testTree.clear();
	}
	cout << "\tdone." << endl
		 << endl;

	return 0;
}
