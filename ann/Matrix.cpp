#include "stdafx.h"
#include "Matrix.h"
#include "Vector.h"

// constructors
Matrix::Matrix()
{
	rows = 0;
	cols = 0;
	p = 0;
}

Matrix::Matrix(int n, double d)
{
	rows = n;
	cols = n;
	p = new Vector[n];
	Vector a = Vector(n);
	for (int r = 0; r < rows; r++)
	{
		p[r] = a;
		p[r][r] = d;
	}
}

Matrix::Matrix(int m, int n)
{
	rows = m;
	cols = n;
	p = new Vector[m];
	Vector a = Vector(n);
	for (int r = 0; r < rows; r++)
		p[r] = a;
}

// copy constructor
Matrix::Matrix(const Matrix& other)
{
	rows = other.rows;
	cols = other.cols;
	p = new Vector[rows];
	for (int r = 0; r < other.rows; r++)
		p[r] = other[r];
}
Matrix::~Matrix()
{
	Destruct();
}

//matrix and matrix operation
Matrix Matrix:: operator + (const Matrix& other) const
{
	Matrix a = *this;
	a += other;
	return a;
}
Matrix Matrix:: operator - (const Matrix& other) const
{
	Matrix a = *this;
	a -= other;
	return a;
}
Matrix Matrix:: operator * (const Matrix& other) const
{
	Matrix a(rows, other.cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < other.cols; j++)
		{
			a[i][j] = p[i] * other.GetColVector(j);
		}
	}
	return a;
}


Matrix Matrix:: operator / (const Matrix& b) const
{
	Matrix a = *this;
	a *= b.Inverse();
	return a;
}

Matrix& Matrix:: operator += (const Matrix& other)
{
	for (int i = 0; i < rows; i++)
		p[i] += other[i];
	return *this;
}
Matrix& Matrix::  operator -= (const Matrix& other)
{
	for (int i = 0; i < rows; i++)
		p[i] -= other[i];
	return *this;
}

Matrix& Matrix::operator *= (const Matrix& b)
{
	Matrix a = *this;
	*this = a*b;
	return *this;
}

Matrix& Matrix:: operator /= (const Matrix& b)
{
	(*this) *= b.Inverse();
	return *this;
}

//matrix and scalar operation
Matrix Matrix:: operator + (double  d) const
{
	Matrix a = *this;
	a += d;
	return a;
}
Matrix Matrix:: operator - (double  d) const
{
	Matrix a = *this;
	a -= d;
	return a;
}

//matrix and scalar operation
Matrix Matrix:: operator * (double  d) const
{
	Matrix a = *this;
	a *= d;
	return a;
}
Matrix Matrix:: operator / (double  d) const
{
	Matrix a = *this;
	a /= d;
	return a;
}

Matrix& Matrix:: operator += (double  d)
{
	for (int i = 0; i < rows; i++)
		p[i] += d;
	return *this;
}

Matrix& Matrix:: operator -= (double  d)
{
	for (int i = 0; i < rows; i++)
		p[i] -= d;
	return *this;
}

Matrix& Matrix:: operator *= (double  d)
{
	for (int i = 0; i < rows; i++)
		p[i] *= d;
	return *this;
}

Matrix& Matrix:: operator /= (double  d)
{
	double x = 1.0 / d;
	*this *= x;
	return *this;
}

//matrix and vector operation
Vector Matrix:: operator * (const Vector& b)
{
	Vector a(b.GetDimension());
	for (int i = 0; i < a.GetDimension(); i++)
		a[i] = p[i].DotProduct(b);
	return a;
}

// assignment operator
Matrix& Matrix:: operator= (const Matrix& a)
{
	Destruct();

	if (this == &a)
		return *this;

	rows = a.rows;
	cols = a.cols;
	p = new Vector[rows];
	for (int r = 0; r < rows; r++)
		p[r] = a[r];
	return *this;
}

//return the row vector of matrix, zero based
Vector Matrix:: operator[] (int row) const
{
	return p[row];
}

//return the row vector of matrix, zero based
Vector& Matrix:: operator[] (int row)
{
	return p[row];
}

Matrix Matrix::Transpose() const
{
	Matrix a(cols, rows);
	for (int i = 0; i < cols; i++)
		a[i] = GetColVector(i);
	return a;
}

Vector& Matrix::GetRowVector(int row) const
{
	return p[row];
}
Vector Matrix::GetRowVector(int row)
{
	return p[row];
}
Vector Matrix::GetColVector(int col) const
{
	Vector a = Vector(rows);
	for (int r = 0; r < rows; r++)
	{
		a[r] = p[r][col];
	}
	return a;
}

int Matrix::GetRowCount() const
{
	return rows;
}

int Matrix::GetColCount() const
{
	return cols;
}

void Matrix::Destruct()
{
	if (p)
	{
		delete[]p;
		p = 0;
		rows = 0;
		cols = 0;
	}
}

//diagonal matrix
Matrix Matrix::Diagonal(int n, double d)
{
	return Matrix(n, d);
}

Matrix Matrix::Identity(int n)
{
	return Matrix(n, 1.0);
}

Matrix& Matrix::RowSwap(int i, int j)
{
	Vector vi = p[i];
	p[i] = p[j];
	p[j] = vi;
	return *this;
}

Matrix Matrix::Inverse() const
{
	//convert
	//A | I
	//to
	//I | B
	//then B is the inverse of A
	//Gauss-Jordan method
	//1. find the max element of column i, let us say the row is k
	//2. swap the row i, and row k
	//3. use row i to eliminate the other rows such that the elements on column i are all zero
	Matrix A(*this);
	Matrix B = Identity(rows);
	for (int i = 0; i < rows; i++)
	{
		//1. find the max element of column i, let us say the row is k
		int k = 0;
		double max = 0.0;
		for (int r = i; r < rows; r++)
		{
			if (Numeric::Abs(A[r][i]) > max)
			{
				max = Numeric::Abs(A[r][i]);
				k = r;
			}
		}

		//2. swap the row i, and row k
		if (i != k)
		{
			A.RowSwap(i, k);
			B.RowSwap(i, k);
			A[i] /= max;
			B[i] /= max;
		}

		//3. use row i to eliminate the other elements in column i such that the elements on column i are all zero
		for (int r = 0; r < rows; r++)
		{
			if (r != i)
			{
				A[r] -= A[i] * A[r][i];
				B[r] -= A[i] * A[r][i];
			}
		}
	}
	return B;
}

double Matrix::Determinate() const
{
	Matrix A(*this);
	Matrix B = Identity(rows);
	int m = 0;
	for (int i = 0; i < rows; i++)
	{
		//1. find the max element of column i, let us say the row is k
		int k = 0;
		double max = 0.0;
		for (int r = i; r < rows; r++)
		{
			if (Numeric::Abs(A[r][i]) > max)
			{
				max = Numeric::Abs(A[r][i]);
				k = r;
			}
		}

		//2. swap the row i, and row k
		if (i != k)
		{
			A.RowSwap(i, k);
			B.RowSwap(i, k);
			m++;
		}

		//3. use row i to eliminate the other elements in column i such that the elements on column i are all zero
		for (int r = i + 1; r < rows; r++)
		{
			double a = A[r][i] / A[i][i];
			A[r] -= A[i] * a;
			B[r] -= A[i] * a;
		}
	}

	double det = -1.0;
	if (m % 2 == 0)
		det = 1.0;
	for (int r = 0; r < rows; r++)
		det *= B[r][r];
	return det;
}

istream& operator>>(istream& s, Matrix& m)
{
	s >> m.rows;
	s >> m.cols;
	m.p = new Vector[m.rows];
	for (int i = 0; i < m.rows; ++i)
		s >> m[i];
	return s;
}
ostream& operator<<(ostream& s, const Matrix& m)
{
	s << m.rows;
	s << m.cols;
	for (int i = 0; i < m.rows; ++i)
		s << m[i];
	return s;
}