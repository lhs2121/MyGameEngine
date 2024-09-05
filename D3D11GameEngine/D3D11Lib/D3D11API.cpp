#include "Pre.h"
#include "D3D11API.h"
#include "ResManager.h"

void CreateResManager(IResManager** ppIResManager)
{
	*ppIResManager = new ResManager();
}

void DeleteResManager(IResManager* pIResManager)
{
	ResManager* castPtr = (ResManager*)pIResManager;
	delete castPtr;
}
	