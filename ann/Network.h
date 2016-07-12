#pragma once
class Vector;
class Matrix;
class Layer;
#include <vector>
using namespace std;

class Network
{
public:
	Network();
	~Network();
	void Add(Layer* p);
	Vector Activate(const Vector& p) const;
	void Train(const Vector& p, const Vector& t);
private:
	vector<Layer*> layers;
	double alpha;
};

