#include <iostream>
#include "mathTree.h"
#include "strAndNum.h"
using namespace std;

class cl
{
public:
	enum en
	{
		a,
		b,
		c
	};
	en e;
	cl(en n) : e(n) {}
};

int main()
{
	mathTree a("a^2+2*x-2");
	a.print();

	return 0;
}