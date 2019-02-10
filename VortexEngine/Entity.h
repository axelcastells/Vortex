#pragma once
#include <map>
#include <memory>
#include <typeindex>
#include "Transform.h"
#include "Component.h"

class Entity {
public:
	Entity(long id);
	~Entity();

	virtual void Update(){}
	virtual void Draw(){}

	void InternalUpdate();
	void InternalDraw();

	inline long GetID() {
		return uniqueID;
	}

	template<typename C>
	inline std::shared_ptr<C> GetComponent() {
		std::type_index index(typeid(C));
		if (childComponents.count(std::type_index(typeid(C))) != 0)
			return std::static_pointer_cast<C>(childComponents[index]);
		else
			return nullptr;
	}

	template<typename C>
	inline void AddComponent() 
	{
		if (childComponents.count(std::type_index(typeid(C))) == 0)
		{
			childComponents[std::type_index(typeid(C))] = std::shared_ptr<C>(new C(uniqueID));
		}
	}

	Transform &GetTransform();
private:
	long uniqueID;
	Transform transform;
	std::map<std::type_index, std::shared_ptr<Component>> childComponents;
};