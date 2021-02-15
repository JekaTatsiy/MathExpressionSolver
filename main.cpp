#include <iostream>
#include "msol.h"

int main()
{
    MSOL::Expr expr("(x+y)*z");
    cout << "graph to (x+y)*z" << endl;
    expr.print();
    cout << "(x+y)*z = " << expr.calc({3, 2, 2}) << " where x=3, y=2, z=2"<<endl<<endl<<endl;

    MSOL::matrix_base_op<int> m(3,3,M_INT_RAND,S_BRACKETS);
    cout << "matrix:" << endl;
    m.print();
    cout << endl << "det=" << m.det();

    return 0;
}
