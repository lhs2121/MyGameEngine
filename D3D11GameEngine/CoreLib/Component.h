#pragma once
#include "Object.h"

class GameObject;
class Component : public Object
{
public:
	Component();
	~Component();

	GameObject* GetParent() const { return (GameObject*)parentObject; }

protected:
};
