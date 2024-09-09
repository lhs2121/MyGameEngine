#include "Pre.h"
#include "Object.h"
#include "Scene.h"

Object::Object()
{
}

Object::~Object()
{
}

Scene* Object::GetScene()
{
	if (pParent != nullptr)
	{
		return pParent->GetScene();
	}
	return (Scene*)this;
}



