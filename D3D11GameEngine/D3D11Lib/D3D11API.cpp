#include "Pre.h"
#include "D3D11API.h"
#include "ResManager.h"
#include "ResourceContainer.h"
#include "ResourceType.h"

STexture* Resource::CreateTexture(const char* _path)
{
	STexture* newTex = new STexture();
    int wideStrSize = MultiByteToWideChar(CP_ACP, 0, _path, -1, NULL, 0);
    wchar_t* wideStr = new wchar_t[wideStrSize];
    int result = MultiByteToWideChar(CP_ACP, 0, _path, -1, wideStr, wideStrSize);

	DirectX::LoadFromTGAFile(wideStr, &newTex->metaData, newTex->scratchImage);

	delete[] wideStr;

	ResourceContainer<STexture>::Resources.insert({ _path, newTex });
	return newTex;
}

void CreateResManager(IResManager** ppIResManager)
{
	*ppIResManager = new ResManager();
}

void DeleteResManager(IResManager* pIResManager)
{
	ResManager* castPtr = (ResManager*)pIResManager;
	delete castPtr;
}
