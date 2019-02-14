#pragma once

#include "Component.h"
#include "Camera.h"
#include "Material.h"
#include <list>
#include "AxisAngle.h"

struct Buffer {
	unsigned int VAO, VBO, EBO;
};

class Renderer : public Component {
public:
	using Component::Component;
	Renderer() = delete;
	~Renderer();

	void Init() override;
	void Update() override;
	void Draw() override;
	
	void SetMeshData(void* vertices, int verticesArrayCount, void* indices, int indicesArrayCount);
	void SetMaterial(Material* mat);
	Material &GetMaterial();
	void SetTransformations(Vortex::Vector3 position, AxisAngle axisAngle/*, Camera &camera*/);
private:
	Buffer* buff;
	Material* material;
};