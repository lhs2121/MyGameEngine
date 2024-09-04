#pragma once
#include "D3D11API.h"

class Texture : public ITexture
{
public:
	Texture();
	~Texture();

	void Setting(ID3D11Device* DevicePtr, EngineFile& _File) override;
	void IntoPipeline(ID3D11DeviceContext* ContextPtr, ShaderType _Type, int SlotNum = 0) override;

	float4 GetImageScale() override;
	ID3D11ShaderResourceView* GetSRV() override;
private:
	ID3D11ShaderResourceView* SRV;
	DirectX::ScratchImage ScratchImage;
	DirectX::TexMetadata MetaData;
};