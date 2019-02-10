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
	// TODO: insertar una instrucción return aquí
}

void EntityComponentSystem::DeleteEntity(long _uniqueId)
{
	entities.erase(_uniqueId);
}

Entity & EntityComponentSystem::GetEntity(long _uniqueId)
{
	return *entities[_uniqueId];
	// TODO: insertar una instrucción return aquí
}

Entity & EntityComponentSystem::GetComponentOwner(long entityId)
{
	// TODO: insertar una instrucción return aquí
	return *entities[entityId];
}
