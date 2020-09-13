#ifndef SMART_MATRIX_H
#define SMART_MATRIX_H

#include "matrix.h"
#include "../MathTree/mathTree.h"

class smartMatrix : public matrix_base_op<mathTree>
{
	public:	
	smartMatrix(int r = 0, int c = 0, int s = S_BRACKETS)
		: matrix_base_op<mathTree>(r, c, s) {}
	smartMatrix(int r, int c, const function<mathTree(int, int)> f, int s = S_BRACKETS)
		: matrix_base_op<mathTree>(r, c, f, s) {}
	smartMatrix(int r, int c, const mathTree **d, int s = S_BRACKETS)
		: matrix_base_op<mathTree>(r, c, d, s) {}
	smartMatrix(int r, int c, const vector<mathTree> d, int s = S_BRACKETS)
		: matrix_base_op<mathTree>(r, c, d, s) {}
	smartMatrix(const vector<vector<mathTree>> d, int s = S_BRACKETS)
		: matrix_base_op<mathTree>(d, s) {}
	smartMatrix(const matrix_data<mathTree> &d)
		: matrix_base_op<mathTree>(d) {}
	smartMatrix(const smartMatrix &d)
		: matrix_base_op<mathTree>(d) {}

	friend matrix_base_op<mathTree> operator*(mathTree, matrix_base_op<mathTree>);
	friend matrix_base_op<mathTree> operator*(matrix_base_op<mathTree>, mathTree);

};


#endif
