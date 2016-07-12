#pragma once
class Vector;
class Matrix;
class TransferFunction;
#include "Vector.h"
#include "Matrix.h"
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

