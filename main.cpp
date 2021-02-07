#include <iostream>
//#include "MathExpr/mathTree.h"
using namespace std;
#include "supportingClasses/str.h"

int main()
{
    str s("0123");
    str a=s.cutInNew(1,2);
    cout << s << " " << a << endl;
    //system("pause");
    return 0;
}