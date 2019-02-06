#include "Entity.h"

Entity::Entity()
{
	components = std::list<Component*>();
	transform = Transform();
}
