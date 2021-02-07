#ifndef MATRIX_BASE_OP_H
#define MATRIX_BASE_OP_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;


//base matrix operations from linear algebra
template <class Type>
class matrix_base_op : public matrix_data<Type>
{
public:
	matrix_base_op(int r = 0, int c = 0, int s = S_BRACKETS)
		: matrix_data<Type>(r, c, s) {}
	matrix_base_op(int r, int c, const function<Type(int, int)> f, int s = S_BRACKETS)
		: matrix_data<Type>(r, c, f, s) {}
	matrix_base_op(int r, int c, const Type **d, int s = S_BRACKETS)
		: matrix_data<Type>(r, c, d, s) {}
	matrix_base_op(int r, int c, const vector<Type> d, int s = S_BRACKETS)
		: matrix_data<Type>(r, c, d, s) {}
	matrix_base_op(const vector<vector<Type>> d, int s = S_BRACKETS)
		: matrix_data<Type>(d, s) {}
	matrix_base_op(const matrix_data<Type> &d)
		: matrix_data<Type>(d) {}
	matrix_base_op(const matrix_base_op<Type> &d)
		: matrix_data<Type>(d) {}

	Type det(int = D_NO_DIR, int = -1);
	matrix_base_op<Type> T();
	matrix_base_op<Type> M(int, int);
	matrix_base_op<Type> A(int, int);
	Type M(int, int, bool);
	Type A(int, int, bool);

	matrix_base_op<Type> operator*(matrix_base_op<Type>);
	matrix_base_op<Type> operator+(matrix_base_op<Type>);

	void addStr(int, int, Type);
	void multStr(int, Type);
	void addCol(int, int, Type);
	void multCol(int, Type);

/*	template <Type>
	friend matrix_base_op<Type> operator*(Type, matrix_base_op<Type>);
	template <Type>
	friend matrix_base_op<Type> operator*(matrix_base_op<Type>, Type);
*/
};

#include "src/matrix_base_op.cpp"

#endif
