#include "Entity.h"

Entity::Entity() {

}

Entity::~Entity() {

}

void Entity::Update()
{
	for (std::map<std::type_index, std::shared_ptr<Component>>::iterator it = childComponents.begin(); it != childComponents.end(); it++) {
		it->second->Update();
	}
}

void Entity::Draw()
{
	for (std::map<std::type_index, std::shared_ptr<Component>>::iterator it = childComponents.begin(); it != childComponents.end(); it++) {
		it->second->Draw();
	}
}
