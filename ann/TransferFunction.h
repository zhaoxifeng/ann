#pragma once
class Vector;
class TransferFunction
{
public:
	TransferFunction()
	{

	}
public:
	double Transfer(double a) const;

	Vector Transfer(const Vector& a) const;

	double FirstDerivative(double a);

	double SecondDerivative(double a);
};
