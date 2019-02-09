#pragma once

#include "Component.h"
#include "Material.h"
#include <list>

struct Buffer {
	unsigned int VAO, VBO, EBO;
};

class Renderer : public Component {
public:
	Renderer();
	~Renderer();

	void Update() override;
	void Draw() override;
	
	void SetMeshData(void* vertices, int verticesArrayCount, void* indices, int indicesArrayCount);
	void SetMaterial(Material* mat);
	Material &GetMaterial();
	void SetTransformations();
private:
	Buffer* buff;
	Material* material;
};