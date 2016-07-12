#include "stdafx.h"
#include "Layer.h"
#include "TransferFunction.h"
#include "Vector.h"
Layer::Layer()
{
	S = 0;
	R = 0;
}
Layer::Layer(int numOfInputs, int numOfNeurons)
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

