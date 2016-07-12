#include "stdafx.h"
#include "Network.h"
#include <vector>
#include "Vector.h"
#include "Layer.h"
#include "Numeric.h"
using namespace std;
using namespace Numeric;

Network::Network()
{
	alpha = 0.5;
}

Network::~Network()
{
}

void Network::Add(Layer* p)
{

}
Vector Network::Activate(const Vector& p) const
{
	vector<Layer*>::const_iterator it;
	Vector a = p;
	for (it = layers.begin(); it != layers.end(); ++it)
		a = (*it)->Activate(a);
	return a;
}
void Network::Train(const Vector& p, const Vector& t)
{
	vector<Vector> ns;
	size_t M = layers.size();
	Vector n = layers[0]->Response(p);
	ns.push_back(n);
	for (size_t m = 1; m < M; m++)
	{
		n = layers[m]->Response(layers[m - 1]->Transfer(n));
		ns.push_back(n);
	}

	Vector a = layers.back()->Transfer(n);
	Vector s = layers[M - 1]->FirstDerivative(n) * (t - a) * (-2.0);
	vector<Vector> ss;
	ss.push_back(s);
	for (int m = M - 2; m >= 1; m--)
	{
		Matrix DF = layers[m]->FirstDerivative(ns[m]);
		Matrix& W = layers[m + 1]->Weight();
		s = DF * W.Transpose() * s;
		ss.push_back(s);
	}
	for (size_t m = 0; m < M; m++)
	{
		Matrix& W = layers[m + 1]->Weight();
		Vector& b = layers[m + 1]->Bias();
		a = layers[m - 1]->Activate(ns[m - 1]);
		W -= alpha * (ss[m] ^ a);
		b -= alpha * ss[m];
	}
}
