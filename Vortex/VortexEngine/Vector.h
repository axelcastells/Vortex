#pragma once

namespace Vortex {
	
	class Vector {
	public:
		float x, y, z;

		Vector();
		Vector(float _x, float _y, float _z);
		~Vector();

		float Normalized();
		void Normalize();
		static Vector Normalize(Vector v);

	};
}