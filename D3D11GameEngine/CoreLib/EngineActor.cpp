#include "Pre.h"
#include "EngineActor.h"

EngineComponent* EngineActor::GetComponent(const char* _Name)
{
	UINT Count = ChildList.GetCount();
	ChildList.GoFirst();

	for (UINT i = 0; i < Count; i++)
	{
		EngineComponent* Child = (EngineComponent*)ChildList.Item();
		if (Child->Name == _Name)
		{
			return Child;
		}
	}
	return nullptr;
}
