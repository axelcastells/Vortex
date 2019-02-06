#pragma once
#include "Shader.h"
#include "Texture.h"

class Material {
public:
	Material(Shader *_shader);
	void SetShader(Shader *_shader);
	Shader &GetShader();

	Texture tex;
private:
	Shader* shader;
};