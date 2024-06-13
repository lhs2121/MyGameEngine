#include <..\EngineBaseLib\IEngineBase.h>
#include <..\EngineBaseLib\EngineDirectory.h>
#include <..\EngineBaseLib\EngineFile.h>
#include <vector>
#include <stdio.h>
#pragma comment(lib,"EngineBaseLib.lib")

int main()
{
	std::vector<EngineFile> Files;
	EngineDirectory dir;
	dir.GoBase();
	dir.GoChild("Asset");
	dir.GetAllFile(&Files);


}