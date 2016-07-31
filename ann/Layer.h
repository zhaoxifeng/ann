#pragma once

#include "Vector.h"
#include "Matrix.h"
#include <iostream>
class Vector;
class Matrix;
class TransferFunction;
using namespace std;
class Layer
{
public:
	Layer();

	Layer(int numOfInputs, int numOfNeurons);

	~Layer();


public:
	Vector Activate(Vector p);
	Vector Response(const Vector& p);
	Vector Transfer(const Vector& n);

	Matrix FirstDerivative(const Vector n);


	Matrix& Weight();


	Vector& Bias();

	friend istream& operator>>(istream& s, Layer& layer);
	friend ostream& operator<<(ostream& s, const Layer& layer);

private:
	//number of neurons
	int S;
	//number of inputs
	int R;
	//bias
	Vector b;
	//weight matrix
	Matrix W;
	//Transfer Function
	TransferFunction* f;
};

