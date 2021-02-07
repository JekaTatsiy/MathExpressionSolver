#include <iostream>
#include <vector>
#include <string.h>
#include <iomanip>

#include "../MathExpr/mathExpr.h"

using namespace std;

void printVec(vector<double> v)
{
	cout << "{";
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << (i == v.size() - 1 ? "" : ", ");
	cout << "}";
}

int main(int argc, char **argv)
{
	bool view = false;
	for (int i = 0; i < argc; i++)
		if ((strcmp(argv[i],"-V")==0) || (strcmp(argv[i], "view")==0))
			view = true;

	cout << "test \"Calculating\": " << endl;

	vector<string> inputTree =
		{"0", "2", "x"};
	vector<vector<double>> inputData =
		{{}, {}, {1}};
	vector<double> resData =
		{0, 2, 1};

	int allAns = inputTree.size();
	int correctAns = 0;
	mathTree testTree;
	for (int i = 0; i < inputTree.size(); i++)
	{
		testTree.set(inputTree[i]);
		double ans = testTree.calc(inputData[i]);
		if (view)
		{
			cout << inputTree[i] << " where variables is ";
			printVec(inputData[i]);
			cout << " = " << ans << ". Correct ans = " << resData[i] << endl;
		}
		if (ans == resData[i])
			correctAns++;
		testTree.clear();
	}
	cout << correctAns << "/" << allAns << " done." << endl << endl;
	return 0;
}
