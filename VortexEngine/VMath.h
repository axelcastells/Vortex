#pragma once
#include "Vector.h"


namespace Vortex {
	namespace Math {
		const float DEG2RAD = 0.0174532924;
		const float RAD2DEG = 57.29578;

		extern double Sqrt(double val);
		extern double Pow(double val, double exponent);
		extern double Clamp(double value, double min, double max);

		extern double Sin(double _angle);
		extern double Cos(double _angle);
		extern double Acos(double _angle);

		extern Vector3 Translate(Vector3 _vec, Vector3 _trans);
		extern Vector3 Rotate(Vector3 _vec, Vector3 _axis, float _angle);
		extern Vector3 Scale(Vector3 _vec, Vector3 _scale);


	}
}