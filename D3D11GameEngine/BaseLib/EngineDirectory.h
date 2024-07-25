#pragma once
#include "EngineString.h"
#include "EngineFile.h"

class EngineFile;
class BaseAPI EngineDirectory
{
public:
	EngineDirectory();

	void GoParent();
	void GoChild(const char* ChildPath);
	void GoBase();

	std::vector<EngineFile> GetAllFile();
	std::vector<EngineFile> GetAllFileExt(const char* _Ext);

private:
	static EngineString BaseDir;
	EngineString Path;
};

