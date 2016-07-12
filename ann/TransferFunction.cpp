#include "stdafx.h"
#include "TransferFunction.h"
#include "Vector.h"
double TransferFunction::Transfer(double a) const
{
	return a;
}
Vector TransferFunction::Transfer(const Vector& a) const
{
	Vector b = a;
	for (int i = 0; i < a.GetDimension(); i++)
		b[i] = Transfer(a[i]);
	return b;
}
double TransferFunction::FirstDerivative(double a)
{
	return a;
}
double TransferFunction::SecondDerivative(double a)
{
	return a;
}
