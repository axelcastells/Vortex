#include "VMath.h"
#include <math.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

double Vortex::Math::Sqrt(double val)
{
	return sqrt(val);
}

double Vortex::Math::Pow(double val, double exponent)
{
	return pow(val, exponent);
}

float Vortex::Math::Clamp(float value, float min, float max)
{
	return (value < min) ? min : (value > max) ? max : value;
}
