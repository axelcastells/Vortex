#include "EntityComponentSystem.hpp"

EntityComponentSystem::EntityComponentSystem() {
	freeEntityId = 0;
}

EntityComponentSystem::~EntityComponentSystem()
{
}

long EntityComponentSystem::GenerateEntityID()
{
	return freeEntityId++;
}

Entity & EntityComponentSystem::CreateEntity(long *outId)
{
	long id = GenerateEntityID();
	entities[id] = new Entity(id);
	*outId = id;
	return *entities[id];
	// TODO: insertar una instrucci�n return aqu�
}

void EntityComponentSystem::DeleteEntity(long _uniqueId)
{
	entities.erase(_uniqueId);
}

Entity & EntityComponentSystem::GetEntity(long _uniqueId)
{
	return *entities[_uniqueId];
	// TODO: insertar una instrucci�n return aqu�
}

Entity & EntityComponentSystem::GetComponentOwner(long entityId)
{
	// TODO: insertar una instrucci�n return aqu�
	return *entities[entityId];
}
