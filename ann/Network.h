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
	void Train(const vector<Vector>& ps, const vector<Vector>& ts);
	friend istream& operator>>(istream& s, Network& network);
	friend ostream& operator<<(ostream& s, const Network& network);

private:
	double PerformanceEvaluation(const vector<Vector>& ps, const vector<Vector>& ts, vector<int>& vs, int m);
	bool IsMonotonicallyIncreasing(vector<double>::const_iterator& start, vector<double>::const_iterator& end);
	vector<Layer*> layers;
	double alpha;
};

