#include "Entity.h"

Entity::Entity(long id)
{
	uniqueID = id;
}

Entity::~Entity() {

}

void Entity::InternalUpdate()
{
	Update();
	for (std::map<std::type_index, std::shared_ptr<Component>>::iterator it = childComponents.begin(); it != childComponents.end(); it++) {
		it->second->Update();
	}
}

void Entity::InternalDraw()
{
	Update();
	for (std::map<std::type_index, std::shared_ptr<Component>>::iterator it = childComponents.begin(); it != childComponents.end(); it++) {
		it->second->Draw();
	}
}
