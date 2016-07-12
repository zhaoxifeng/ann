#pragma once
class Matrix;
class Vector;
namespace Numeric
{
	const double kZero = 1.0e-8;

	double Abs(double d);

	bool IsZero(double d);

	Matrix operator* (double a, const Matrix& m);

	Vector operator* (double a, const Vector& v);

};
