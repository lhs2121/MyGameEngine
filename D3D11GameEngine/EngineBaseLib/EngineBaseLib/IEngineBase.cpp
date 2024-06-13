#include "Pre.h"
#include "IEngineBase.h"
#include "EngineMemoryPool.h"
#include "EngineDirectory.h"

void CreateMemoryPool(IEngineMemoryPool** ppMemoryPool)
{
	*ppMemoryPool = new EngineMemoryPool();
}

void CreateDir(IEngineDirectory** ppDirectory)
{
	*ppDirectory = new EngineDirectory();
}
