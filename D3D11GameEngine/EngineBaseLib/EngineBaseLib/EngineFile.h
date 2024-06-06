#pragma once
#include "EnginePath.h"

class __declspec(dllexport) EngineFile : public EnginePath
{
public:
	// constrcuter destructer
	EngineFile();
	EngineFile(const char* _Path);

	~EngineFile();

	EngineString GetFileName();
};

