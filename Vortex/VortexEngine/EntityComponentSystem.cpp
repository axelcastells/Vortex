#include "EntityComponentSystem.hpp"

EntityComponentSystem::~EntityComponentSystem()
{
}

Entity & EntityComponentSystem::CreateEntity()
{
	entities.push_back(new Entity());
	return *entities.back();
	// TODO: insertar una instrucción return aquí
}
