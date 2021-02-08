#include <cassert>
#include "../Number.h"

USING_MATSOLV

template <char T>
void Number<T>::initAsINT(str line)
{
    while (!line.is_empty())
    {
    }
}
template <char T>
void Number<T>::initAsFLT(str line)
{
}
template <char T>
void Number<T>::initAsVAR(str line)
{
}
template <char T>
Number<T>::Number()
{
    num_byte = nullptr;
    separator = 0;
}
template <char T>
Number<T>::Number(str input_line)
{
    switch (T)
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
template <char T>
Number<T>::Number(str input_line, char type) : Number(input_line)
{
    info |= type;
}
template <char T>
Number<T>::Number(smartMatrix *input_matr)
{
    if (TYPE(T) != MATR)
        assert("different types");
    info |= MATR;
    matr = input_matr;
}
template <char T>
char Number<T>::getInfo()
{
    return info;
}
