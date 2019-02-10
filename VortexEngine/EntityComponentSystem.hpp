#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include "Component.h"

#define ECS EntityComponentSystem::Instance()
class EntityComponentSystem {
public:

	EntityComponentSystem(EntityComponentSystem const&) = delete;
	EntityComponentSystem& operator=(EntityComponentSystem const&) = delete;
	~EntityComponentSystem();

	static std::shared_ptr<EntityComponentSystem> Instance() {
		static std::shared_ptr<EntityComponentSystem> instance{ new EntityComponentSystem };
		return instance;
	}

	Entity &CreateEntity();
	Component &CreateComponent(Entity* owner);
private:
	EntityComponentSystem();

	std::vector<Entity*> entities;
	std::vector<Component*> components;
	std::vector < std::pair<Entity&, Component&>> relations;
};