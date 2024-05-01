#include "Pre.h"
#include "IEngineD3DRes.h"
#include "EngineD3DResourceManager.h"

void CreateD3DResourceManger(IEngineD3DResourceManager** ppManager)
{
	*ppManager = new EngineD3DResourceManager();
}
	