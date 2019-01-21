#pragma once
#include "Transform.h"
#include "Component.h"
#include <list>
#include <iostream>


class Entity {
public:
	Entity();
	~Entity();

	template<class C>
	inline Component & GetComponent()
	{
		try {
			for (std::list<Component*>::iterator it = components.begin(); it != components.end(); it++) {
				if (dynamic_cast<C>(it))
					return it;
			}

			throw "Component";
			// TODO: insertar una instrucción return aquí
		}
		catch (std::string exception) {
			std::cout << "Couldn't find component of class: " << exception << std::endl;
		}

	}

	template<class C>
	inline void AddComponent(Component *comp) {
		components.push_back(comp);
	}

private:
	Transform transform;
	std::list<Component*> components;
};


