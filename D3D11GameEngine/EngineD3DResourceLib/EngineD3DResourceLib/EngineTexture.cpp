#include "Pre.h"
#include "EngineTexture.h"


EngineTexture::EngineTexture()
{
}

EngineTexture::~EngineTexture()
{
}

void EngineTexture::Setting(EngineFile& _File)
{
	wchar_t* UniPath = nullptr;
	EngineString Ext = _File.GetExt();


	if (Ext == ".png")
	{
		_File.GetPath().GetUTF8(&UniPath);
		DirectX::LoadFromWICFile(UniPath, DirectX::WIC_FLAGS_NONE, &MetaData, ScratchImage);
	}
	else if (Ext == ".dds")
	{
		_File.GetPath().GetUTF8(&UniPath);
		DirectX::LoadFromDDSFile(UniPath, DirectX::DDS_FLAGS_NONE, &MetaData, ScratchImage);
	}
	else if (Ext == ".tga")
	{
		_File.GetPath().GetUTF8(&UniPath);
		DirectX::LoadFromTGAFile(UniPath, DirectX::TGA_FLAGS_NONE, &MetaData, ScratchImage);
	}
	else
	{
		return;
	}

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
