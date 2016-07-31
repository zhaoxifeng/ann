#pragma once
#include <iostream>
#include "StreamSupportBase.h"
#include "NameBasedFactory.h"
using namespace std;
class Vector;
class TransferFunction : public StreamSupportBase
{
public:
	TransferFunction()
	{
	}
public:

	static TransferFunction* Instance();
	static DerivedRegister<TransferFunction> sTransferFunctionCreator;

public:
	double Transfer(double a) const;

	Vector Transfer(const Vector& a) const;

	double FirstDerivative(double a);

	double SecondDerivative(double a);

	friend istream& operator>>(istream& s, TransferFunction* v);
	friend ostream& operator<<(ostream& s, const TransferFunction& v);
};
