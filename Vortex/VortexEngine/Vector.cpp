#include "Vector.h"
#include "VMath.h"

using namespace Vortex;

Vector::Vector() {

}

Vector::Vector(float _allValues) {
	x = y = z = _allValues;
}

Vector::Vector(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}
Vector::~Vector() {

}

void Vortex::Vector::Normalize()
{
	*this = Normalize(*this);
}

Vector Vortex::Vector::Normalized()
{
	Vector n = Normalize(*this);
	return n;
}

Vector Vortex::Vector::Normalize(Vector v)
{
	float mod = (float)Math::Sqrt(Math::Pow(v.x, 2) + Math::Pow(v.y, 2) + Math::Pow(v.z, 2));
	v.x /= mod;
	v.y /= mod;
	v.z /= mod;
	return v;
}

Vector Vortex::Vector::operator+(Vector v)
{
	return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vortex::Vector::operator-(Vector v)
{
	return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vortex::Vector::operator*(Vector v)
{
	return Vector(x * v.x, y * v.y, z * v.z);
}

Vector Vortex::Vector::operator/(Vector v)
{
	return Vector(x / v.x, y / v.y, z / v.z);
}

Vector Vortex::Vector::operator*(float f)
{
	return Vector(x * f, y * f, z * f);
}

Vector Vortex::Vector::Cross(Vector l, Vector r)
{
	return Vector(	l.y * r.z - l.z * r.y,
					l.z * r.x - l.x * r.z,
					l.x * r.y - l.y * r.x);
}

double Vortex::Vector::Dot(Vector l, Vector r)
{
	return ((l.x * r.x) + (l.y * r.y) + (l.z * r.z));
}

float Vortex::Vector::Magnitude(Vector v)
{
	return (float)Math::Sqrt(Math::Pow(v.x, 2) + Math::Pow(v.y, 2) + Math::Pow(v.z, 2));
}

float Vortex::Vector::Magnitude()
{
	return Magnitude(*this);
}


