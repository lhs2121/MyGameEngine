#include "Pre.h"
#include "EngineTexture.h"


EngineTexture::EngineTexture()
{
}

EngineTexture::~EngineTexture()
{
}

void EngineTexture::Setting(EngineString _FilePath)
{
	wchar_t* UniPath = nullptr;
	_FilePath.GetUTF8(&UniPath);
	DirectX::LoadFromWICFile(UniPath, DirectX::WIC_FLAGS_FILTER_POINT, &MetaData, ScratchImage);
	DirectX::CreateShaderResourceView(DevicePtr->GetDevice(), ScratchImage.GetImages(), ScratchImage.GetImageCount(), MetaData, &SRV); 

	if (UniPath != nullptr)
	{
		delete[] UniPath;
		UniPath = nullptr;
	}
}

void EngineTexture::Release()
{
	SRV->Release();
	ScratchImage.Release();
}

ID3D11ShaderResourceView* EngineTexture::GetSRV()
{
	return SRV;
}

float4 EngineTexture::GetImageScale()
{
	float4 Scale = { (float)MetaData.width,(float)MetaData.height };
	return Scale;
}
