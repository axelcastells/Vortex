#include "Entity.h"

Entity::Entity() {

}

Entity::~Entity() {

}

void Entity::AddComponent(Component* comp) {
	childComponents.push_back(comp);
}

Component &Entity::GetComponent() {
	return *childComponents[0];
}