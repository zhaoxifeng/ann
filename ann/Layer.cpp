#include "stdafx.h"
#include "Layer.h"
#include "TransferFunction.h"
#include "Vector.h"
#include <fstream>

Layer::Layer()
{
	S = 0;
	R = 0;
}
Layer::Layer(int numOfNeurons, int numOfInputs) : S(numOfNeurons), R(numOfInputs), W(S, R)
{

}
Layer::~Layer()
{

}

Vector Layer::Activate(Vector p)
{
	return f->Transfer(W * p + b);
}
Vector Layer::Response(const Vector& p)
{
	return W * p + b;
}
Vector Layer::Transfer(const Vector& n)
{
	return f->Transfer(n);
}
Matrix Layer::FirstDerivative(const Vector n)
{
	Matrix DF(S, S);
	for (int i = 0; i < S; i++)
		DF[i][i] = f->FirstDerivative(n[i]);
	return DF;
}

Matrix& Layer::Weight()
{
	return W;
}

Vector& Layer::Bias()
{
	return b;
}

istream& operator>>(istream& s, Layer& layer)
{
	s >> layer.S;
	s >> layer.R;
	s >> layer.W;
	s >> layer.b;
	s >> layer.f;
	return s;
}

ostream& operator<<(ostream& s, const Layer& layer)
{
	s << layer.S;
	s << layer.R;
	s << layer.W;
	s << layer.b;
	s << *layer.f;
	return s;
}
