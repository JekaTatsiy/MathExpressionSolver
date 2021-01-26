#include <iostream>
#include "MathExpr/mathTree.h"
using namespace std;

int main()
{
 //   mathTree expr("sin(x^2)^4+1");
    mathTree expr("2^2+x");
    expr.print(std::cout,false,true);
    //cout << expr.calc()<<endl;
    cout << expr.calc({-1})<<endl;
    cout << expr.calc({-2})<<endl;

    system("pause");
    return 0;
}