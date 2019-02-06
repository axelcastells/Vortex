#include "Material.h"

Material::Material(Shader *_shader)
{
	shader = _shader;
	tex = Texture();
}

void Material::SetShader(Shader *_shader)
{
	shader = _shader;
}

Shader & Material::GetShader()
{
	return *shader;
}
