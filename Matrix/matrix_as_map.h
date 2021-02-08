#ifndef MATRIX_AS_MAP_H
#define MATRIX_AS_MAP_H

#include "../MathSolver.h"
#include "Matrix.h"
//use matrix as map
BEG_MATSOLV
USING_MATSOLV
template <class Type>
class matrix_as_map : public matrix_data<Type>{
public:
	matrix_as_map(int r = 0, int c = 0, int s = S_BRACKETS)
		: matrix_data<Type>(r, c, s) {}
	matrix_as_map(int r, int c, const function<Type(int, int)> f, int s = S_BRACKETS)
		: matrix_data<Type>(r, c, f, s) {}
	matrix_as_map(int r, int c, const Type **d, int s = S_BRACKETS)
		: matrix_data<Type>(r, c, d, s) {}
	matrix_as_map(int r, int c, const vector<Type> d, int s = S_BRACKETS)
		: matrix_data<Type>(r, c, d, s) {}
	matrix_as_map(const vector<vector<Type>> d, int s = S_BRACKETS)
		: matrix_data<Type>(d, s) {}
	matrix_as_map(const matrix_data<Type> &d)
		: matrix_data<Type>(d) {}
	matrix_as_map(const matrix_base_op<Type> &d)
		: matrix_data<Type>(d) {}

	
		
};

#include "src/matrix_as_map.cpp"
END_MATSOLV
#endif
