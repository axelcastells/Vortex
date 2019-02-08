#pragma once

#include "Component.h"
#include "Material.h"
#include <list>

struct Buffer {
	unsigned int VAO, VBO, EBO;
};

class Renderer : Component {
public:
	Renderer();
	~Renderer();

	void Draw();
	void SetMaterial(Material* mat);
	void SetTransformations();
	void SetMeshData(void* vertices, int verticesArrayCount, void* indices, int indicesArrayCount);
private:
	Buffer* buff;
	Material* material;
	std::list<float> vertexData;
	std::list<float> indexData;
};