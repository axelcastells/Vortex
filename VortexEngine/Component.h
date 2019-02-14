#pragma once

class Component {
public:
	explicit Component(long _ownerId) {
		SetOwnerID(_ownerId);
	}

	inline void SetOwnerID(long _ownerId) {
		ownerId = _ownerId;
	}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	//Entity &GetOwner();
private:
	long ownerId;
};

