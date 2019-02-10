#pragma once
#include "Component.h"
#include "VMath.h"

class Camera : public Component {
public:
	using Component::Component;

	void Init() override;
	void Draw() override;
	void Update() override;
private:

};