#pragma once

#include "EngineMath.h"

extern "C" __declspec(dllexport) struct IEngineDirectory
{
	virtual void GoParent(const char* ) = 0
	virtual void GoChild() = 0
}
