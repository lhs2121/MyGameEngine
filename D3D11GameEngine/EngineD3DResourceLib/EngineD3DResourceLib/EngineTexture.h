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

	void Setting(EngineFile& _File) override;
	void SetDevicePtr(EngineDevice* _DevicePtr)
	{
		DevicePtr = _DevicePtr;
	}
	void Release() override;
	ID3D11ShaderResourceView* GetSRV() override;
	float4 GetImageScale() override;

	void IntoPipeLine(ShaderType _Type, int SlotNum = 0) override;
private:
	EngineDevice* DevicePtr;
	ID3D11ShaderResourceView* SRV;
	DirectX::ScratchImage ScratchImage;
	DirectX::TexMetadata MetaData;
};