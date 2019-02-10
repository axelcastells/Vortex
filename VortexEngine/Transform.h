#pragma once
#include "Vector.h"
#include "Quaternion.h"

using namespace Vortex;

class Transform {
public:
private:
	Vector3 position;
	Vector3 scale;
	Quaternion rotation;
};