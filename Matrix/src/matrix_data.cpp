#include "../matrix_data.h"

using namespace std;

inline int len(int v)
{
	return log10(abs(v)) + 1 + (v < 0);
}



//~~~~~~~~~~~~~~~~~~~~~~
//~~~~ constructors ~~~~
//~~~~~~~~~~~~~~~~~~~~~~

template <typename T>
inline matrix_data<T>::matrix_data(int r, int c, int s)
{
	rows = r;
	columns = c;
	style = s;
	createMatrix();
//	initMatrix(M_ZERO);
}

template <typename T>
inline matrix_data<T>::matrix_data(int r, int c, const function<T(int, int)> &f, int s) : matrix_data(r, c, s) { initMatrix(f); }

//template <typename T>
//inline matrix_data<T>::matrix_data(int r, int c, const T **d, int s) : matrix_data(r, c, s) { initMatrix(d); }

template <typename T>
inline matrix_data<T>::matrix_data(int r, int c, const vector<T> &d, int s) : matrix_data(r, c, s) { initMatrix(d); }

template <typename T>
inline matrix_data<T>::matrix_data(const vector<vector<T>> &d, int s) : matrix_data(d.size(), d[0].size(), s) { initMatrix(d); }

template <typename T>
inline matrix_data<T>::matrix_data(const matrix_data<T> &m) : matrix_data(m.rows, m.columns, m.style) { initMatrix(m.matr); }

template <typename T>
inline matrix_data<T>::~matrix_data()
{
	erase();
}

//~~~~~~~~~~~~~~~~~~~~~~
//~~~~ modification ~~~~
//~~~~~~~~~~~~~~~~~~~~~~

template <typename T>
inline void matrix_data<T>::erase()
{

	for (int i = 0; i < rows; i++)
	{
		delete matr[i];
		matr[i] = nullptr;
	}
	delete matr;
	matr = nullptr;
	rows = 0;
	columns = 0;
}

template <typename T>
inline int matrix_data<T>::calcMaxLen()
{
	int maxLen = 0;
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
			if (maxLen < len(matr[i][j]))
				maxLen = len(matr[i][j]);
	return maxLen;
}

template <typename T>
inline void matrix_data<T>::createMatrix()
{
	matr = new T *[rows];
	for (int i = 0; i < rows; i++)
		matr[i] = new T[columns];
}

template <typename T>
inline void matrix_data<T>::initMatrix(T **data)
{
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
			matr[i][j] = data[i][j];
}

template <typename T>
inline void matrix_data<T>::initMatrix(const vector<T> &data)
{
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
			matr[i][j] = data[i * columns + j];
}

template <typename T>
inline void matrix_data<T>::initMatrix(const vector<vector<T>> &data)
{
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
			matr[i][j] = data[i][j];
}

template <typename T>
inline void matrix_data<T>::initMatrix(const function<T(int, int)> &func)
{
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
			matr[i][j] = func(i, j);
}

template <typename T>
inline void matrix_data<T>::reinit(const function<T(int, int)> &func) { initMatrix(func); }

template <typename T>
inline matrix_data<T> &matrix_data<T>::reinit(int r, int c, const function<T(int, int)> &f)
{
	erase();
	(*this) = matrix_data<T>(r, c, f, style);
	return *this;
}

//~~~~~~~~~~~~~~~~~~~~~~
//~~~~  get params  ~~~~
//~~~~~~~~~~~~~~~~~~~~~~

template <typename T>
inline T matrix_data<T>::get(int i, int j)
{
	return (*this)(i, j);
}

template <typename T>
inline T** matrix_data<T>::Matr() { return matr; }

template <typename T>
inline int matrix_data<T>::Rows() { return rows; }

template <typename T>
inline int matrix_data<T>::Columns() { return columns; }

template <typename T>
inline int matrix_data<T>::Style() { return style; }

template <typename T>
inline matrix_data<T> matrix_data<T>::getRow(int num)
{
	return matrix_data<T>(1, columns, [&](int i, int j) -> T { return matr[num][j]; });
}

template <typename T>
inline matrix_data<T> matrix_data<T>::getColumn(int num)
{
	return matrix_data<T>(Rows, 1, [&](int i, int j) -> T { return matr[i][num]; });
}

template <typename T>
inline matrix_data<T> matrix_data<T>::getMatrix(int r, int c)
{
	return matrix_data<T>(r, c, [&](int i, int j) -> T { return matr[i][j]; });
}

template <typename T>
inline matrix_data<T> matrix_data<T>::getRect(int up_l_r, int up_l_c, int r, int c)
{
	return matrix_data<T>(r, c, [&](int i, int j) -> T { return matr[up_l_r + i][up_l_c + j]; });
}

template <typename T>
inline T &matrix_data<T>::operator()(int r, int c)
{
	assert(r >= 0 && r < rows);
	assert(c >= 0 && c < columns);
	return matr[r][c];
}

template <typename T>
inline matrix_data<T> &matrix_data<T>::operator=(const matrix_data<T> &m)
{
	if (this != &m)
	{
		erase();
		rows = m.rows;
		columns = m.columns;
		style = m.style;
		createMatrix();
		initMatrix(m.matr);
	}
	return *this;
}

template <typename T>
inline T *matrix_data<T>::operator[](int i)
{
	assert(i >= 0 && i < rows);
	return matr[i];
}

//~~~~~~~~~~~~~~~~~~~~~~
//~~~~  out matrix  ~~~~
//~~~~~~~~~~~~~~~~~~~~~~

template <typename T>
std::ostream &operator<<(std::ostream &out, matrix_data<T> m)
{
	m.print(out);
	return out;
}

template <typename T>
inline void matrix_data<T>::print(std::ostream &out)
{
	int maxLen = calcMaxLen();
	maxLen += maxLen == 0;

	if (rows < 1 || columns < 1)
	{
		out << "| no matrix | " << endl;
		return;
	}

	switch (style)
	{
	case S_VOID:
		printVoid(out, maxLen);
		break;
	case S_BRACKETS:
		printBrackets(out, maxLen);
		break;
	case S_TWO_LINES:
		printTwoLines(out, maxLen);
		break;
	case S_GRID:
		printGrid(out, maxLen);
		break;

	default:
		out << "style not found\n";
		break;
	}
}

template <typename T>
inline void matrix_data<T>::printVoid(std::ostream &out, int maxLen)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
			out << setw(maxLen + 1) << matr[i][j] << " ";
		out << endl;
	}
}

template <typename T>
inline void matrix_data<T>::printBrackets(std::ostream &out, int maxLen)
{
	for (int i = 0; i < rows; i++)
	{
		out << (rows == 1 ? '<' : (i == 0 ? '/' : (i == rows - 1 ? '\\' : '|')));
		for (int j = 0; j < columns; j++)
			out << setw(maxLen + 1) << matr[i][j] << " ";
		out << (rows == 1 ? '>' : (i == 0 ? '\\' : (i == rows - 1 ? '/' : '|'))) << endl;
	}
}

template <typename T>
inline void matrix_data<T>::printTwoLines(std::ostream &out, int maxLen)
{
	for (int i = 0; i < rows; i++)
	{
		out << '|' << ' ';
		for (int j = 0; j < columns; j++)
			out << setw(maxLen + 1) << matr[i][j] << " ";
		out << '|' << endl;
	}
}
template <typename T>
inline void matrix_data<T>::printGrid(std::ostream &out, int maxLen)
{
	assert("need create function");
}
