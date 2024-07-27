#pragma once
#include "BaseAPI.h"
#include <Windows.h>

class EngineTime : public IEngineTime
{
public:
	void  Init() override;
	void  CountStart() override;
	float CountEnd() override;

protected:
	LARGE_INTEGER Frequency;
	LARGE_INTEGER Start;
	LARGE_INTEGER End;
};

