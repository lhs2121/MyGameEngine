#include "Pre.h"
#include "EngineTexture.h"
#include <DirectXTex.h>

#pragma comment(lib, "DirectXTex.lib")

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
