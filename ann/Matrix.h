#pragma once
#include "Numeric.h"
class Vector;
class Matrix
{
public:
	// constructors
	Matrix();
	Matrix(int n, double d = 1.0);
	Matrix(int m, int n);
	// copy constructor
	Matrix(const Matrix& other);
	~Matrix();

	//matrix and matrix operation
	Matrix operator + (const Matrix& other) const;

	Matrix operator - (const Matrix& other) const;

	Matrix operator * (const Matrix& other) const;

	Matrix operator / (const Matrix& b) const;


	Matrix& operator += (const Matrix& other);

	Matrix& operator -= (const Matrix& other);


	Matrix& operator *= (const Matrix& b);


	Matrix& operator /= (const Matrix& b);


	//matrix and scalar operation
	Matrix operator + (double  d) const;

	Matrix operator - (double  d) const;


	//matrix and scalar operation
	Matrix operator * (double  d) const;

	Matrix operator / (double  d) const;


	Matrix& operator += (double  d);


	Matrix& operator -= (double  d);


	Matrix& operator *= (double  d);


	Matrix& operator /= (double  d);


	//matrix and vector operation
	Vector operator * (const Vector& b);


	// assignment operator
	Matrix& operator= (const Matrix& a);


	//return the row vector of matrix, zero based
	Vector operator[] (int row) const;


	//return the row vector of matrix, zero based
	Vector& operator[] (int row);

	Matrix Transpose() const;


	Vector& GetRowVector(int row) const;

	Vector GetRowVector(int row);

	Vector GetColVector(int col) const;


	int GetRowCount() const;


	int GetColCount() const;


	void Destruct();


	//diagonal matrix
	static Matrix Diagonal(int n, double d = 1.0);


	static Matrix Identity(int n);


	Matrix& RowSwap(int i, int j);

	Matrix Inverse() const;


	double Determinate() const;
private:
	int rows;
	int cols;
	Vector* p;
};



