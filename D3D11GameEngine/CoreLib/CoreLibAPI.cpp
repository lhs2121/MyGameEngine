#include "Pre.h"
#include "CoreLibAPI.h"
#include "EngineCore.h"

void CreateEngineCore(ICore** pICore, const char* _Tilte, float4 _WindowPos, float4 _WindowSize, HINSTANCE _hInstance, IObject* _ContentsObject)
{
	*pICore = new EngineCore();

}
