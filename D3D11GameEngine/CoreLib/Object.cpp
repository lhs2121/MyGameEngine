#include "Pre.h"
#include "Object.h"
#include "Level.h"

Object::Object()
{
}

Object::~Object()
{
}

Level* Object::GetLevel()
{
	if (pParent != nullptr)
	{
		return pParent->GetLevel();
	}
	return (Level*)this;
}



