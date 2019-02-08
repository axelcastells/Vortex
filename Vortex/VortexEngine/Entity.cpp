#include "Entity.h"

void Entity::AddComponent(Component* comp) {
	childComponents.push_back(comp);
}