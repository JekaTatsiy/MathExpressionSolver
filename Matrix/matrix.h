#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <functional>
#include <math.h>
#include <assert.h>
using namespace std;

#include "../MathSolver.h"
#include "../Expr/Expr.h"

BEG_MATSOLV
USING_MATSOLV

#ifndef CORRECT_ADRES
	#ifdef ADDRESSES_AS_MATH
		#define CORRECT_ADRES -1
	#else
		#define CORRECT_ADRES 0
	#endif
#endif

#define S_VOID 0
#define S_BRACKETS 1
#define S_TWO_LINES 2
#define S_GRID 3

#define D_NO_DIR 10
#define D_ROW 11
#define D_COL 12

#define M_ZERO [](int i, int j) -> int { return 0; }
#define M_IDENTITY [](int i, int j) -> int { return i == j; }
#define M_INT_RAND [](int i, int j) -> int { return rand() % 19 - 9; }
#define M_INPUT_INT [](int i, int j) -> int { int v; cin >> v; return v; }
#define M_INPUT_FLT [](int i, int j) -> float { float v; cin >> v; return v; }

#define CALC true
#define NO_CALC false

	//base matrix operations with data
	template <class T>
	class matrix_data;

	//base matrix operations from linear algebra
	template <class T>
	class matrix_base_op;

	//use matrix as map
	template <class T>
	class matrix_as_map;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "matrix_data.h"
#include "matrix_base_op.h"
#include "matrix_as_map.h"
#include "smartMatrix.h"

	typedef vector<vector<int>> intVecMatr;
	typedef vector<vector<float>> fltVecMatr;
	typedef matrix_base_op<int> intMatr;
	typedef matrix_base_op<float> fltMatr;
	typedef matrix_as_map<int> intMap;
	typedef matrix_as_map<float> fltMap;

END_MATSOLV

#endif
