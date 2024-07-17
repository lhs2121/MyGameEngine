#include "Pre.h"
#include "CoreAPI.h"
#include "EngineCore.h"

void CreateEngineCore(ICore** pICore)
{
	*pICore = new EngineCore();

}
