#include <iostream>
#include <string>
#include "mathExpr.h"

using namespace std;

int main(int argc,char**argv)
{
	if(argc==2)
		mathTree(argv[1]).print();

	mathTree a("");
	a.print(std::cout,true);
	a.clear();

	return 0;
}
