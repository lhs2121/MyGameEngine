#include "Windows.h"
#include <string>
#include <map>
#include <vector>
#include <EngineBaseLib\EngineBaseLib\EngineBaseInterface.h>
#pragma comment(lib,"EngineBaseLib.lib")

int main()
{
	EngineDebug::CrtSetDbgFlag();

	{
		IEngineMemoryPool* mp;
		CreateEngineMemoryPool(&mp);
		mp->Init(1024, 24);

		DeleteEngineMemoryPool(mp);
		mp = nullptr;
	}
	
}