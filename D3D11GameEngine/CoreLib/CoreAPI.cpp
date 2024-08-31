#include "Pre.h"
#include "CoreAPI.h"
#include "EngineCore.h"

void CreateEngineCore(ICore** ppInterface)
{
	*ppInterface = new EngineCore();
}

void DeleteEngineCore(ICore* pInterface)
{
	EngineCore* castptr = (EngineCore*)pInterface;
	delete castptr;
}
