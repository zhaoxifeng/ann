#include "stdafx.h"
#include "Numeric.h"
#include "Matrix.h"
#include "Vector.h"
namespace Numeric
{
	double Abs(double d)
	{
		if (d > 0)
			return d;
		else
			return -d;
	}

	bool IsZero(double d)
	{
		return Abs(d) < kZero;
	}

	Matrix operator* (double a, const Matrix& m)
	{
		return m * a;
	}

	Vector operator* (double a, const Vector& v)
	{
		return v * a;
	}
}
