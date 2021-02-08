#ifndef NUMBER_H
#define NUMBER_H

#include "../MathSolver.h"
#include "../Matrix/Matrix.h"
#include "../SupCls/SupCls.h"

BEG_MATSOLV
USING_MATSOLV
/*
┌─┬─┬─┬─┬─┬─┬─┬─┐
|7│6│5│4│3│2│1│0│
├─┼─┼─┼─┼─┼─┼─┼─┤
│0│ │ │ │ │ │ │ │->sign(-)
│1│ │ │ │ │ │ │ │->sign(+)
├─┼─┼─┼─┼─┼─┼─┼─┤
│ │ │ │ │ │ │ │1│->undef
├─┼─┼─┼─┼─┼─┼─┼─┤
│ │ │ │ │ │ │1│ │->inf
│ │ │ │ │ │1│ │ │->nan
├─┼─┼─┼─┼─┼─┼─┼─┤
│ │ │ │ │1│ │ │ │->INT   11 -34 0
│ │ │ │1│ │ │ │ │->FLT   0.0 -4.232342
│ │ │1│ │ │ │ │ │->VAR   x a1 ax
├─┼─┼─┼─┼─┼─┼─┼─┤
│ │1│ │ │ │ │ │ │->MATR (ptr)
└─┴─┴─┴─┴─┴─┴─┴─┘
*/

#define MINUS   0b10000000
#define PLUS    0b00000000
#define UNDEF   0b00000001
#define inf     0b00000010
#define nan     0b00000100
#define INT     0b00001000
#define FLT     0b00010000
#define VAR     0b00100000
#define MATR    0b01000000

    template <char T>
    class Number
    {
        char info = T;
        char *num_byte;
        int separator;
        smartMatrix *matr;

        void initAsINT(str);
        void initAsFLT(str);
        void initAsVAR(str);

    public:
        Number();
        Number(str);
        Number(str, char);
        Number(smartMatrix *);

        char getInfo();
    };

#define TYPE(mask)  (mask) & INT & FLT & VAR & MATR 
} // namespace mathSolver

#endif