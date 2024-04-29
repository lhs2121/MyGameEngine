#pragma once
#include "EngineCore.h"
#include "EngineDevice.h"

template<typename ResourceType>
class EngineD3DResource
{
public:
	// constrcuter destructer
	EngineD3DResource() {};
	virtual ~EngineD3DResource() {};

	// delete Function
	EngineD3DResource(const EngineD3DResource& _Other) = delete;
	EngineD3DResource(EngineD3DResource&& _Other) noexcept = delete;
	EngineD3DResource& operator=(const EngineD3DResource& _Other) = delete;
	EngineD3DResource& operator=(EngineD3DResource&& _Other) noexcept = delete;

	static ResourceType* RegisterResource(std::string Name)
	{
		ResourceType* NewResource = new ResourceType();
		Resources.insert(std::make_pair(Name, NewResource));
		return NewResource;
	}
	static void DeleteAllResource();

	static ResourceType* Find(std::string Name)
	{
		return Resources[Name];
	}
	
	virtual void IntoPipeLine() = 0;
	
	static std::map<std::string, ResourceType*> Resources;
};

template<typename ResourceType>
std::map<std::string, ResourceType*> EngineD3DResource<ResourceType>::Resources;

template<typename ResourceType>
void EngineD3DResource<ResourceType>::DeleteAllResource()
{
	for (std::pair<std::string, ResourceType*> pair : Resources)
	{
		EngineD3DResource* ResourcePtr = pair.second;

		if (ResourcePtr != nullptr)
		{
			delete ResourcePtr;
			ResourcePtr = nullptr;
		}
	}
	Resources.clear();
}
