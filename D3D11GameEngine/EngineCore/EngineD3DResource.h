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

	static ResourceType* CreateResource(std::string Name)
	{
		ResourceType* NewResource = new ResourceType();
		Resources.insert(std::make_pair(Name, NewResource));
		return NewResource;
	}

	static ResourceType* Find(std::string Name)
	{
		return Resources[Name];
	}

	virtual void IntoPipeLine() = 0;

	static std::map<std::string, ResourceType*> Resources;
};

template<typename ResourceType>
std::map<std::string, ResourceType*> EngineD3DResource<ResourceType>::Resources;
