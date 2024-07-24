#pragma once

#include <Windows.h>

class BaseAPI EngineTime
{
public:
	void Init();
	void CountStart();
	float CountEnd();

protected:
	LARGE_INTEGER Frequency;
	LARGE_INTEGER Start;
	LARGE_INTEGER End;
};

