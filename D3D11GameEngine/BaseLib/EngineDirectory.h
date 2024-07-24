#pragma once
#include "EngineString.h"

class BaseAPI EngineDirectory
{
public:
	EngineDirectory();

	void GoParent();
	void GoChild(const char* ChildPath);
	void GoBase();

	void GetAllFile(void* vector);
	void GetAllFileExt(void* vector, const char* _Ext);

private:
	static EngineString BaseDir;
	EngineString Path;
};

