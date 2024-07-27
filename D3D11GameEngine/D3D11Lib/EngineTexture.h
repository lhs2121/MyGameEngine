#pragma once
#include "D3D11API.h"

class EngineTexture : public IEngineTexture
{
public:
	EngineTexture();
	~EngineTexture();

	void Setting(EngineFile& _File) override;
	void IntoPipeLine(ShaderType _Type, int SlotNum = 0) override;

	float4 GetImageScale() override;
	ID3D11ShaderResourceView* GetSRV() override;
private:
	void SetDevice(ID3D11Device* _DevicePtr) override { DevicePtr = _DevicePtr; }
	void SetContext(ID3D11DeviceContext* _ContextPtr) override { ContextPtr = _ContextPtr; }

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
	ID3D11ShaderResourceView* SRV;
	DirectX::ScratchImage ScratchImage;
	DirectX::TexMetadata MetaData;
};