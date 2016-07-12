#pragma once
class Matrix;
class Vector
{
public:
	Vector();
	explicit Vector(int dim);
	Vector(const Vector& other);
	~Vector();

	Vector& operator= (const Vector& other);

	double operator[] (int i) const;

	double& operator[] (int i);

	double Get(int i) const;

	Vector operator+ (const Vector& other) const;

	Vector& operator+= (const Vector& other);

	Vector operator- (const Vector& other) const;

	Vector& operator-= (const Vector& other);

	Vector operator+ (double d) const;
	Vector& operator+= (double d);

	Vector operator- (double d) const;
	Vector& operator-= (double d);

	Vector operator* (double d) const;


	Vector& operator*= (double d);
	Vector operator/ (double d) const;
	Vector& operator/= (double d);

	Vector CrossProduct(const Vector& other) const;
	double operator* (const Vector other) const;
	double DotProduct(const Vector& other) const;

	Matrix MatrixProduct(const Vector& other) const;
	Matrix AsRowMatrix() const;
	Matrix AsColMatrix() const;
	Matrix operator^ (const Vector& other) const;
	int GetDimension() const;
	void Destruct();
private:
	int n;
	double* p;
};

