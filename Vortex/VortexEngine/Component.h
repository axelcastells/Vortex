#pragma once

class Component {
protected:
	virtual void Update() = 0;
	virtual void Draw() = 0;

	//Entity &GetOwner();
private:
};