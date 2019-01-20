#pragma once
#include "Transform.h"
#include "Component.h"
#include <list>


class Entity {
public:
	Entity();
	~Entity();

	template<class C>
	Component &GetComponent(C componentType);

private:
	Transform transform;
	std::list<Component> components;
};