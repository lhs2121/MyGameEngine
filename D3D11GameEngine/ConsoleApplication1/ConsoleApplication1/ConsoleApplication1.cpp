#include <EngineBaseLib\EngineBaseLib\IEngineBase.h>
#include <vector>
#pragma comment(lib,"EngineBaseLib.lib")

int main()
{
	std::vector<IEngineFile> Files;
	IEngineDirectory* dir;
	CreateDir(&dir);
	dir->GoBase();
	dir->GoChild("Asset");
	dir->GetAllFile(&Files);
}