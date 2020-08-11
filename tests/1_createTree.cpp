#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "../mathExpr.h"

using namespace std;

int main()
{
	vector<string> inputData = 
	    {"","a", "x+y", "a+b+c", "a*(b+c)", "a*b+c", "(a+b)/(c-d)", "a+(b*c^2)", 
        "1+2+3+x", "1+2+3+x", "sin(a^2)^(1/2)", "log(2,e)"};

	mathTree testTree;
    for(auto i : inputData)
    {
		testTree.set(i);
		testTree.clear();
	}
	
	cout << "test \"create tree\" done " << endl; 
	return 0;
}
