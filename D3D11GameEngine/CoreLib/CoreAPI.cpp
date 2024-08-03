#include "Pre.h"
#include "CoreAPI.h"
#include "EngineCore.h"
#include "Singleton.h"

void CreateEngineCore(ICore** ppInterface)
{
	MainCore = new EngineCore();
	*ppInterface = MainCore;

}

void DeleteEngineCore(ICore* pInterface)
{
	EngineCore* castptr = (EngineCore*)pInterface;
	delete castptr;
}
