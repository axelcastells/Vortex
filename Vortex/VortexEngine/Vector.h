#pragma once

namespace Vortex {
	
	class Vector {
	public:
		float x, y, z;

#pragma region Constructors & Destructor
		Vector();
		Vector(float _allValues);
		Vector(float _x, float _y, float _z);
		~Vector();
#pragma endregion

#pragma region Operators
		Vector operator+(Vector v);
		Vector operator-(Vector v);
		Vector operator*(Vector v);
		Vector operator/(Vector v);

		Vector operator*(float f);
#pragma endregion

		inline static Vector Zero() { return Vector(0); }
		inline static Vector One() { return Vector(1); }

		static Vector Normalize(Vector v);
		void Normalize();
		Vector Normalized();

		static Vector Cross(Vector l, Vector r);
		static double Dot(Vector l, Vector r);

		static float Magnitude(Vector v);
		float Magnitude();
	};
}