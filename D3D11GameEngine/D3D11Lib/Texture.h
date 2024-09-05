#pragma once
#include "D3D11API.h"

class Texture : public ITexture
{
public:
	Texture();
	~Texture();

	void Setting( EngineFile& _File) override;
	void IntoPipeline(ShaderType _Type, int SlotNum = 0) override;

	float4 GetImageScale() override;
	ID3D11ShaderResourceView* GetSRV() override;

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
private:
	ID3D11ShaderResourceView* SRV;
	DirectX::ScratchImage ScratchImage;
	DirectX::TexMetadata MetaData;
};