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
	std::string Path = _FilePath;
	std::wstring UniPath = EngineString::GetWideString(Path);
	DirectX::LoadFromWICFile(UniPath.c_str(), DirectX::WIC_FLAGS_FILTER_POINT, &MetaData, ScratchImage);
	DirectX::CreateShaderResourceView(DevicePtr->GetDevice(), ScratchImage.GetImages(), ScratchImage.GetImageCount(), MetaData, &SRV);
}

void EngineTexture::Release()
{
	SRV->Release();
	ScratchImage.Release();
}
