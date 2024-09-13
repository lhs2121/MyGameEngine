#include "Pre.h"
#include "InputObject.h"
#include "Scene.h"

bool InputObject::GetKeyDown(int _key)
{
	return Input::IsDown(_key, this);
}

bool InputObject::GetKeyPress(int _key)
{
	return Input::IsPress(_key, this);
}

bool InputObject::GetKeyUp(int _key)
{
	return Input::IsUp(_key, this);
}

bool InputObject::GetKeyFree(int _key)
{
	return Input::IsFree(_key,this);
}
