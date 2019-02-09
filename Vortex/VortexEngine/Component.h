#pragma once
#include "Transform.h"

class Component {
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;

	//Entity &GetOwner();
private:
};

class NullComponent : public Component {
public:
	void Update() override;
	void Draw() override;
	NullComponent(){}
};