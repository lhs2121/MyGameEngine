#include "Pre.h"
#include "IEngineD3DResource.h"
#include "EngineD3DResourceManager.h"

void CreateD3DResourceManger(IEngineD3DResourceManager** ppManager)
{
	*ppManager = new EngineD3DResourceManager();
}
	