#include "Pre.h"
#include "D3D11API.h"
#include "EngineD3DManager.h"

void CreateEngineD3DManager(IEngineD3DManager** ppEngineManager)
{
	*ppEngineManager = new EngineD3DManager();
}

void DeleteEngineD3DManager(IEngineD3DManager* pEngineManager)
{
	EngineD3DManager* castPtr = (EngineD3DManager*)pEngineManager;
	delete castPtr;
}
	