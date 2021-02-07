#include "../matrix_base_op.h"

template <class Type>
inline Type matrix_base_op<Type>::det(int dir, int lineNum)
{
	assert(this->Rows() == this->Columns() && " ����� ������ ���� �����?�.");
	assert((lineNum < 0 || dir != D_NO_DIR) && " �? ������ ��?�, ������ ���� ������ ���?�����.");

	if (this->Rows() > 3 || lineNum != -1)
	{
		int targetLine = lineNum;
		int targetDir = dir;
		if (lineNum == -1)
		{
			int targetLineR = 0;
			int targetLineC = 0;
			int maxCountZeroR = 0;
			int maxCountZeroC = 0;
			int curZeroR;
			int curZeroC;

			for (int i = 0; i < this->Rows(); i++)
			{
				curZeroR = 0;
				curZeroC = 0;
				for (int j = 0; j < this->Rows(); j++)
				{
					if ((dir == D_ROW || dir == D_NO_DIR) && (*this)(i, j) == 0)
						++curZeroR;
					if ((dir == D_COL || dir == D_NO_DIR) && (*this)(j, i) == 0)
						++curZeroC;
				}

				if (curZeroR > maxCountZeroR)
				{
					maxCountZeroR = curZeroR;
					targetLineR = i;
				}
				if (curZeroC > maxCountZeroC)
				{
					maxCountZeroC = curZeroC;
					targetLineC = i;
				}
				if (maxCountZeroC > maxCountZeroR)
				{
					targetLine = targetLineC;
					targetDir = D_COL;
				}
				else
				{
					targetLine = targetLineR;
					targetDir = D_ROW;
				}
			}
		}

		Type res = 0;
		for (int i = 0; i < this->Rows(); i++)
		{

			if (targetDir == D_ROW)
				res += (*this)(targetLine, i) * this->A(targetLine, i, CALC);
			else if (targetDir == D_COL)
				res += (*this)(i, targetLine) * this->A(i, targetLine, CALC);
		}
		return res;
	}
	else
	{
		if (this->Rows() == 1)
		{
			return (*this)(0, 0);
		}
		else if (this->Rows() == 2)
		{
			return (*this)(0, 0) * (*this)(1, 1) - (*this)(1, 0) * (*this)(0, 1);
		}
		else if (this->Rows() == 3)
		{
			return (*this)(0, 0) * (*this)(1, 1) * (*this)(2, 2) + (*this)(0, 1) * (*this)(1, 2) * (*this)(2, 0) + (*this)(1, 0) * (*this)(2, 1) * (*this)(0, 2) - (*this)(0, 2) * (*this)(1, 1) * (*this)(2, 0) - (*this)(0, 1) * (*this)(1, 0) * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 1) * (*this)(0, 0);
		}
		else
		{
			assert(this->Rows()<=0 && "������ ?��� �����.");
			return 0;
		}
	}
}

template <class Type>
inline matrix_base_op<Type> matrix_base_op<Type>::T()
{
	return (*this) = matrix_base_op<Type>(
			   this->Columns(),
			   this->Rows(),
			   [&](int i, int j) -> Type { return this->Matr()[j][i]; },
			   this->Style());
}

template <class Type>
inline matrix_base_op<Type> matrix_base_op<Type>::M(int i_arg, int j_arg)
{
	assert(this->Rows() == this->Columns() && " ����� ������ ���� �����?�.");
	//	i_arg += CORRECT_ADRES;
	//	j_arg += CORRECT_ADRES;
	return matrix_base_op<Type>(
		this->Rows() - 1,
		this->Columns() - 1,
		[&](int i, int j) -> Type { return this->Matr()[i + (i >= i_arg)][j + (j >= j_arg)]; },
		this->Style());
}

template <class Type>
inline matrix_base_op<Type> matrix_base_op<Type>::A(int i_arg, int j_arg)
{
	return Type(pow(-1, i_arg + j_arg)) * this->M(i_arg, j_arg);
}

template <class Type>
inline Type matrix_base_op<Type>::M(int i_arg, int j_arg, bool mode)
{
	return this->M(i_arg, j_arg).det();
}

template <class Type>
inline Type matrix_base_op<Type>::A(int i_arg, int j_arg, bool mode)
{
	return Type(pow(-1, i_arg + j_arg)) * this->M(i_arg, j_arg, mode);
}

template <class Type>
matrix_base_op<Type> matrix_base_op<Type>::operator*(matrix_base_op<Type> b)
{
	assert(this->Columns() == b.Rows());
	return matrix_base_op<Type>(
		this->Rows(),
		b.Columns(),
		[&](int i, int j) -> Type {	Type res=0;
			for(int k = 0; k < this->Columns(); k++) res += (*this)[i][k] * b[k][j]; 
			return res; },
		this->Style());
}

template <class Type>
matrix_base_op<Type> matrix_base_op<Type>::operator+(matrix_base_op<Type> b)
{
	assert(this->Rows() == b.Rows() && this->Columns() == b.Columns());
	return matrix_base_op<Type>(
		this->Rows(),
		b.Columns(),
		[&](int i, int j) -> Type { return (*this)[i][j] + b[i][j]; },
		this->Style());
}

template <typename Type>
inline void matrix_base_op<Type>::addStr(int to, int with, Type coef)
{
	for (int i = 0; i < this->Columns(); i++)
		(*this)[to][i] += (*this)[with][i] * coef;
}

template <typename Type>
inline void matrix_base_op<Type>::multStr(int to, Type coef)
{
	for (int i = 0; i < this->Columns(); i++)
		(*this)[to][i] *= coef;
}

template <typename Type>
inline void matrix_base_op<Type>::addCol(int to, int with, Type coef)
{
	for (int i = 0; i < this->Columns(); i++)
		(*this)[i][to] += (*this)[i][with] * coef;
}

template <typename Type>
inline void matrix_base_op<Type>::multCol(int to, Type coef)
{
	for (int i = 0; i < this->Columns(); i++)
		(*this)[i][to] *= coef;
}

//~~~~~~~~~~~~~~~~~~~~~~
//~~~~   friends    ~~~~
//~~~~~~~~~~~~~~~~~~~~~~
/*
template <class Type>
Type det(const matrix_base_op<Type> &arg)
{
}

template <class Type>
matrix_base_op<Type> transp(const matrix_base_op<Type> &arg)
{

	return matrix_base_op<Type>(arg).T();
}

template <class Type>
matrix_base_op<Type> operator*(Type a, matrix_base_op<Type> b)
{
	return matrix_base_op<Type>(
		b.Rows(),
		b.Columns(),
		[&](int i, int j) -> Type { return b[i][j] * a; },
		b.Style());
}

template <class Type>
matrix_base_op<Type> operator*(matrix_base_op<Type> a, Type b)
{
	return b * a;
}*/
