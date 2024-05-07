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
}

void EngineTexture::Release()
{
	ScratchImage.Release();
}
