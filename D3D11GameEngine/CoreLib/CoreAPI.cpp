#include "Pre.h"
#include "CoreAPI.h"
#include "EngineCore.h"
#include "Singleton.h"

void CreateEngineCore(ICore** pICore)
{
	MainCore = new EngineCore();
	*pICore = MainCore;

}
