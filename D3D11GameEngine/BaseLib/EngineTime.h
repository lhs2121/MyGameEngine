#pragma once
#include "BaseAPI.h"
#include <Windows.h>

class EngineTime : public ITime
{
public:
	void  Init() override;
	void  CountStart() override;
	float CountEnd() override;

protected:
	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;
};

