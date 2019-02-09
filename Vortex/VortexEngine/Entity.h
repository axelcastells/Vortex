#pragma once
#include <vector>
#include "Transform.h"
#include "Component.h"

class Entity {
public:
	Entity();
	~Entity();

	Component &GetComponent();
	void AddComponent(Component* comp);

	Transform &GetTransform();
private:
	Transform transform;
	std::vector<Component*> childComponents;
};