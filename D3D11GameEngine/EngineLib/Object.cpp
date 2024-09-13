#include "Pre.h"
#include "Object.h"
#include "Scene.h"

Object::Object()
{
	transform.parentObject = this;
}

Object::~Object()
{
}

