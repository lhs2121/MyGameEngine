#include "Pre.h"
#include "Texture.h"


Texture::Texture()
{
}

Texture::~Texture()
{
	SRV->Release();
	ScratchImage.Release();
}

void Texture::Setting(EngineFile& _File)
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

	DirectX::CreateShaderResourceView(DevicePtr, ScratchImage.GetImages(), ScratchImage.GetImageCount(), MetaData, &SRV); 

	if (UniPath != nullptr)
	{
		delete[] UniPath;
		UniPath = nullptr;
	}
}

ID3D11ShaderResourceView* Texture::GetSRV()
{
	return SRV;
}

float4 Texture::GetImageScale()
{
	float4 Scale = { (float)MetaData.width,(float)MetaData.height };
	return Scale;
}

void Texture::IntoPipeline( ShaderType _Type, int SlotNum)
{
	switch (_Type)
	{
	case ShaderType::VS:
		ContextPtr->VSSetShaderResources(SlotNum, 1, &SRV);
		break;
	case ShaderType::PS:
		ContextPtr->PSSetShaderResources(SlotNum, 1, &SRV);
		break;
	case ShaderType::CS:
		break;
	case ShaderType::HS:
		break;
	case ShaderType::DS:
		break;
	case ShaderType::GS:
		break;
	default:
		break;
	}
	
}
