#pragma once

namespace Vortex {
	namespace Math {
		const float DEG2RAD = 0.0174532924;
		const float RAD2DEG = 57.29578;

		extern double Sqrt(double val);
		extern double Pow(double val, double exponent);
		extern float Clamp(float value, float min, float max);
	}
}