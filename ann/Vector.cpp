#include "stdafx.h"
#include "Vector.h"
#include "Matrix.h"

Vector::Vector()
{
	n = 0;
	p = 0;
}
Vector::Vector(int dim)
{
	n = dim;
	p = new double[n];
	for (int i = 0; i < n; i++)
		p[i] = 0.0;
}
Vector::Vector(const Vector& other)
{
	n = other.n;
	p = new double[n];
	for (int i = 0; i < n; i++)
		p[i] = other[i];
}
Vector::~Vector()
{
	Destruct();
}

Vector& Vector::operator= (const Vector& other)
{
	Destruct();
	n = other.n;
	p = new double[n];
	for (int i = 0; i < n; i++)
		p[i] = other[i];
	return *this;
}

double Vector::operator[] (int i) const
{
	return p[i];
}

double& Vector::operator[] (int i)
{
	return p[i];
}

double Vector::Get(int i) const
{
	return p[i];
}

Vector Vector::operator+ (const Vector& other) const
{
	Vector a = *this;
	a += other;
	return a;
}

Vector& Vector::operator+= (const Vector& other)
{
	for (int i = 0; i < n; i++)
		p[i] += other[i];
	return *this;
}

Vector Vector::operator- (const Vector& other) const
{
	Vector a = *this;
	a -= other;
	return a;
}

Vector& Vector::operator-= (const Vector& other)
{
	for (int i = 0; i < n; i++)
		p[i] -= other[i];
	return *this;
}

Vector Vector::operator+ (double d) const
{
	Vector a = *this;
	a += d;
	return a;
}
Vector& Vector::operator+= (double d)
{
	for (int i = 0; i < n; i++)
		p[i] += d;
	return *this;
}

Vector Vector::operator- (double d) const
{
	Vector a = *this;
	a -= d;
	return a;

}
Vector& Vector::operator-= (double d)
{
	*this += -d;
	return *this;
}

Vector Vector::operator* (double d) const
{
	Vector a = *this;
	a *= d;
	return a;
}


Vector& Vector::operator*= (double d)
{
	for (int i = 0; i < n; i++)
		p[i] *= d;
	return *this;
}

Vector Vector::operator/ (double d) const
{
	Vector a = *this;
	a /= d;
	return a;
}
Vector& Vector::operator/= (double d)
{
	for (int i = 0; i < n; i++)
		p[i] /= d;
	return *this;
}

Vector Vector::CrossProduct(const Vector& other) const
{
	return *this;
}
double Vector::operator* (const Vector other) const
{
	return DotProduct(other);
}
double Vector::DotProduct(const Vector& other) const
{
	double d = 0;
	for (int i = 0; i < n; i++)
		d += p[i] * other[i];
	return d;
}

Matrix Vector::MatrixProduct(const Vector& other) const
{
	//column vector a
	//row vector b
	return AsColMatrix() * other.AsRowMatrix();
}

Matrix Vector::operator^ (const Vector& other) const
{
	//column vector a
	//row vector b
	return AsColMatrix() * other.AsRowMatrix();
}

Matrix Vector::AsRowMatrix() const
{
	Matrix a(1);
	a[0] = *this;
	return a;

}

Matrix Vector::AsColMatrix() const
{
	Matrix a(1);
	a[0] = *this;
	return a.Transpose();
}


int Vector::GetDimension() const
{
	return n;
}

void Vector::Destruct()
{
	if (p)
	{
		delete[]p;
		p = 0;
		n = 0;
	}
}

istream& operator >> (istream& s, Vector& v)
{
	s >> v.n;
	v.p = new double[v.n];
	for (int i = 0; i < v.n; ++i)
		s >> v[i];
	return s;
}

ostream& operator<<(ostream& s, const Vector& v)
{
	s << v.n;
	for (int i = 0; i < v.n; ++i)
		s << v[i];
	return s;
}
