#include "Pre.h"
#include "EngineTexture.h"


EngineTexture::EngineTexture()
{
}

EngineTexture::~EngineTexture()
{
}

void EngineTexture::Setting(const char* _FilePath)
{
	EngineString Path = _FilePath;
	wchar_t* UniPath = nullptr;
	Path.GetUTF8(&UniPath);
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
