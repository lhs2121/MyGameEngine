#include "Pre.h"
#include "EngineD3DInterface.h"
#include "EngineD3DManager.h"

void EngineAPI CreateEngineD3DManager(IEngineD3DManager** ppManager)
{
	*ppManager = new EngineD3DManager();
}
	