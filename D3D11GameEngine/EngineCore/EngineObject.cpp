#include "Pre.h"
#include "EngineObject.h"

EngineObject::EngineObject()
{
}

EngineObject::~EngineObject()
{
	for (EngineObject* Child : ChildList)
	{
		if (Child != nullptr)
		{
			delete Child;
			Child = nullptr;
		}
	}
}

void EngineObject::Start()
{
}

void EngineObject::ChildUpdate(float _Delta)
{
	for (EngineObject* Object : ChildList)
	{
		Object->Update(_Delta);
	}
}

void EngineObject::Update(float _Delta)
{

}

void EngineObject::Release()
{
}
