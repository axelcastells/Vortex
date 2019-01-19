#pragma once
#include "Shader.h"

class Material {
public:
	Material(Shader _shader);
	void SetShader(Shader _shader);
	Shader &GetShader();
private:
	Shader shader;
};