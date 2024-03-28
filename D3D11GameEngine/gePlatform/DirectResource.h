#pragma once
#include "EngineCore.h"
#include "EngineDevice.h"

template<typename ResourceType>
class DirectResource
{
public:
	// constrcuter destructer
	DirectResource() {};
	virtual ~DirectResource() {};

	// delete Function
	DirectResource(const DirectResource& _Other) = delete;
	DirectResource(DirectResource&& _Other) noexcept = delete;
	DirectResource& operator=(const DirectResource& _Other) = delete;
	DirectResource& operator=(DirectResource&& _Other) noexcept = delete;

	static ResourceType* CreateResource(std::string Name)
	{
		ResourceType* NewResource = new ResourceType();
		Resources.insert(std::make_pair(Name, NewResource));
		return NewResource;
	}
	virtual void IntoPipeLine() = 0;

private:
	static std::map<std::string, ResourceType*> Resources;
};

template<typename ResourceType>
std::map<std::string, ResourceType*> DirectResource<ResourceType>::Resources;
