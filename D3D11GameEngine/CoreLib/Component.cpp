#include "Pre.h"
#include "Component.h"

Component::Component()
{
}

Component::~Component()
{
}

GameObject* Component::GetParent()
{
	return (GameObject*)pParent;
}
