#pragma once
#include <map>
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
	Entity &CreateEntity(long *outId);
	void DeleteEntity(long _uniqueId);

	Entity &GetEntity(long _uniqueId);

	Entity &GetComponentOwner(long entityId);

private:
	EntityComponentSystem();
	long freeEntityId;
	long GenerateEntityID();
	std::map<long, Entity*> entities;
};