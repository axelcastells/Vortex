#pragma once
#include "Component.h"
#include <list>


class Entity {
public:
	Entity();
	~Entity();

private:
	std::list<Component> components;

};