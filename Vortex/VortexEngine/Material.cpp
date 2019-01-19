#include "Material.h"

Material::Material(Shader _shader)
{
	SetShader(_shader);
}

void Material::SetShader(Shader _shader)
{
	shader = _shader;
}

Shader & Material::GetShader()
{
	return shader;
}
