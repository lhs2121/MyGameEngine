#pragma once
#include "EngineD3DInterface.h"

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

	void Setting(EngineString _FilePath) override;
	void SetDevicePtr(EngineDevice* _DevicePtr)
	{
		DevicePtr = _DevicePtr;
	}
	void Release() override;
	ID3D11ShaderResourceView* GetSRV();
private:
	EngineDevice* DevicePtr;
	ID3D11ShaderResourceView* SRV;
	DirectX::ScratchImage ScratchImage;
	DirectX::TexMetadata MetaData;
};