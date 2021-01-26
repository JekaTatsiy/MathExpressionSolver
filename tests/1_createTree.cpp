#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "../MathExpr/mathExpr.h"

using namespace std;

int main(int argc, char **argv)
{
	bool view = false;
	if (argc == 2 && (argv[1] == "-V") || (argv[1] == "view"))
		view=true;

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
	cout << "\tdone." << endl << endl;

	return 0;
}
