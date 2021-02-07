#pragma once
#ifndef MATRIX_DATA_H
#define MATRIX_DATA_H

#include <vector>
#include <functional>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <assert.h>
#include "matrix.h"


//base matrix operations with data
template <class T>
class matrix_data
{
	T **matr;
	int rows;
	int columns;
	int style;

	int calcMaxLen();
	void printVoid(std::ostream &,int);
	void printBrackets(std::ostream &,int);
	void printTwoLines(std::ostream &,int);
	void printGrid(std::ostream &,int);

	void createMatrix();
	void initMatrix(T **);
	void initMatrix(const std::vector<T>&);
	void initMatrix(const std::vector<std::vector<T>>&);
	void initMatrix(const std::function<T(int, int)>&);

public:
	matrix_data(int = 0, int = 0, int = S_BRACKETS);
	matrix_data(int, int, const std::function<T(int, int)>& = M_ZERO, int = S_BRACKETS);
	matrix_data(int, int, const T **, int = S_BRACKETS);
	matrix_data(int, int, const std::vector<T>&, int = S_BRACKETS);
	matrix_data(const std::vector<std::vector<T>>&, int = S_BRACKETS);
	matrix_data(const matrix_data<T> &);
	~matrix_data();
	void erase();

	void reinit(const std::function<T(int, int)>&);
	matrix_data<T> &reinit(int, int, const std::function<T(int, int)>&);

	void setRow(int, matrix_data<T>&);
	void setColumn(int, matrix_data<T>&);

	T get(int, int);
	T** Matr();
	int Rows();
	int Columns();
	int Style();

	matrix_data<T> getRow(int);
	matrix_data<T> getColumn(int);
	matrix_data<T> getMatrix(int, int);
	matrix_data<T> getRect(int, int, int, int);

	T &operator()(int, int);
	matrix_data<T> &operator=(const matrix_data<T> &);
	T *operator[](int);

	void print(std::ostream & = cout);
};

#include "src/matrix_data.cpp" 

#endif
