#pragma once
#include "EngineString.h"

class __declspec(dllexport) EnginePath
{
public:
	// constrcuter destructer
	EnginePath()
	{
	}

	EnginePath(EngineString _Path);

	virtual ~EnginePath()
	{
	}

	EngineString& GetPath();

	EngineString Path;
};

