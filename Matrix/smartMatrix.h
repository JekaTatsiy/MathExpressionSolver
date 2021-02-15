#ifndef SMART_MATRIX_H
#define SMART_MATRIX_H

#include "Matrix.h"

USING_MATSOLV

class smartMatrix : public matrix_base_op<Expr>
{
	public:	
	smartMatrix(int r = 0, int c = 0, int s = S_BRACKETS)
		: matrix_base_op<Expr>(r, c, s) {}
	smartMatrix(int r, int c, const function<Expr(int, int)> f, int s = S_BRACKETS)
		: matrix_base_op<Expr>(r, c, f, s) {}
	smartMatrix(int r, int c, const Expr **d, int s = S_BRACKETS)
		: matrix_base_op<Expr>(r, c, d, s) {}
	smartMatrix(int r, int c, const vector<Expr> d, int s = S_BRACKETS)
		: matrix_base_op<Expr>(r, c, d, s) {}
	smartMatrix(const vector<vector<Expr>> d, int s = S_BRACKETS)
		: matrix_base_op<Expr>(d, s) {}
	smartMatrix(const matrix_data<Expr> &d)
		: matrix_base_op<Expr>(d) {}
	smartMatrix(const smartMatrix &d)
		: matrix_base_op<Expr>(d) {}

	friend matrix_base_op<Expr> operator*(Expr, matrix_base_op<Expr>);
	friend matrix_base_op<Expr> operator*(matrix_base_op<Expr>, Expr);

};


#endif
