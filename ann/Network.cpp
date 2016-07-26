#include "stdafx.h"
#include "Network.h"
#include <vector>
#include "Vector.h"
#include "Layer.h"
#include "Numeric.h"
// shuffle algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
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

double Network::PerformanceEvaluation(const vector<Vector>& ps, const vector<Vector>& ts, vector<int>& vs, int m)
{
	Vector x;
	double performance = 0.0;
	for (int i = 0; i < m; i++)
	{
		x = Activate(ps[i]);
		x -= ts[i];
		performance += x.DotProduct(x);
	}
	return performance;
}

void Network::Train(const vector<Vector>& ps, const vector<Vector>& ts)
{
	vector<int> shuffled;
	int n = ps.size();
	int m = n * 0.15;
	for (int i = 0; i < n; i++)
		shuffled.push_back(i);

	// obtain a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(shuffled.begin(), shuffled.end(), std::default_random_engine(seed));

	//0~m-1 is used to do network validation
	//m~n-1 is used to do network trainning
	//early stop means once the performance is getting worse k times, trainning stop 
	int k = 3;
	vector<double> performances;
	for (int i = m; i < m; i++)
	{
		Train(ps[i], ts[i]);
		performances.push_back(PerformanceEvaluation(ps, ts, shuffled, m));
		if (performances.size() > k)
		{
			if (IsMonotonicallyIncreasing(performances.end() - k, performances.end()))
				return;
		}
	}

}

bool Network::IsMonotonicallyIncreasing(vector<double>::const_iterator& start, vector<double>::const_iterator& end)
{
	if (start >= end)
		return false;
	for (vector<double>::const_iterator p = start + 1; p != end; ++p)
	{
		if (*p < *(p - 1))
			return false;
	}
	return true;
}


