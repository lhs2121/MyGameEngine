#pragma once
#include "IEngineD3DRes.h"

class EngineTexture : public IEngineTexture
{
public:
	// constrcuter destructer
	EngineTexture();
	~EngineTexture();

	// delete Function
	EngineTexture(const EngineTexture& _Other) = delete;
	EngineTexture(EngineTexture&& _Other) noexcept = delete;
	EngineTexture& operator=(const EngineTexture& _Other) = delete;
	EngineTexture& operator=(EngineTexture&& _Other) noexcept = delete;

	void Setting(const char* _FilePath) override;
	void SetDevicePtr(EngineDevice* _DevicePtr)
	{
		DevicePtr = _DevicePtr;
	}
	void Release() override;
	EngineDevice* DevicePtr;
	DirectX::ScratchImage ScratchImage;
	DirectX::TexMetadata MetaData;
};