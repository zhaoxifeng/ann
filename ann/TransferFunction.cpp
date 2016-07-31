#include "stdafx.h"
#include "TransferFunction.h"
#include "Vector.h"

DerivedRegister<TransferFunction> TransferFunction::sTransferFunctionCreator("TransferFunction");

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

TransferFunction* TransferFunction::Instance()
{
	static TransferFunction instance;
	return &instance;
}

istream& operator >> (istream& s, TransferFunction* v)
{
	int n = 0;
	s >> n;
	char* p = new char[n + 1];
	s.read(p, n);
	p[n] = '\0';
	string str(p);
	v = (TransferFunction*) NameBasedFactory::createInstance(str);
	delete []p;
	return s;
}

ostream& operator << (ostream& s, const TransferFunction& v)
{
	string str("TransferFunction");
	s << str.length();
	s.write(str.c_str(), str.length());
	return s;
}
