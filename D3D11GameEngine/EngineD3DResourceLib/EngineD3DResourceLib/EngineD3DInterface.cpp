#include "Pre.h"
#include "EngineD3DInterface.h"
#include "EngineD3DManager.h"

void CreateEngineD3DManager(IEngineD3DManager** ppEngineManager)
{
	*ppEngineManager = new EngineD3DManager();
}

void DeleteEngineD3DManager(IEngineD3DManager* pEngineManager)
{
	delete dynamic_cast<EngineD3DManager*>(pEngineManager);
}
	