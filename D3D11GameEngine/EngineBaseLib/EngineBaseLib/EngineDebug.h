#pragma once
#include "EngineString.h"
#include <functional>
class EngineBaseAPI EngineDebug
{
public:
	static void CrtSetBreakAlloc(UINT Number);
	static void CrtSetDbgFlag();
	static void MsgBoxAssert(EngineString ErrorMsg);
	static double CalculateTime(std::function<void()> ExecuteTarget, int ExecuteCount);
};

