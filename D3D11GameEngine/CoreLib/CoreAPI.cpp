#include "Pre.h"
#include "CoreAPI.h"
#include "Engine.h"

void CreateEngine(ICore** ppInterface)
{
	*ppInterface = new Engine();
}

void DeleteEngine(ICore* pInterface)
{
	Engine* castptr = (Engine*)pInterface;
	delete castptr;
}
