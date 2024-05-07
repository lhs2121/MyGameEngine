#pragma once
#include "IEngineD3DRes.h"
#include "DirectXTex.h"
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
;
	void SetDevicePtr(ID3D11DeviceContext* pDeviceContext)
	{
		DeviceContext = pDeviceContext;
	}
	ID3D11DeviceContext* DeviceContext;
	DirectX::ScratchImage ScratchImage;
	DirectX::TexMetadata MetaData;
};