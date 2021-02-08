#include "../Number.h"
#include <cassert>

void initAsINT(str line)
{
    while(!line.is_empty())
    {
        
    }
}
void initAsFLT(str line)
{
}
void initAsVAR(str line)
{
}

Number(str input_line, char type = INT)
{
    info |= type;
    switch (type)
    {
    case INT:
        initAsINT(input_line);
        break;
    case FLT:
        initAsINT(input_line);
        break;
    case VAR:
        initAsINT(input_line);
        break;

    default:
        assert("error type");
    }
}
Number(smartMatrix *input_matr)
{
    info |= MATR;
    matr = input_matr;
}
