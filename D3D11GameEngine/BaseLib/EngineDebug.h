#pragma once
#include "EngineString.h"

class BaseAPI EngineDebug
{
public:
	static void CrtSetBreakAlloc(UINT Number);
	static void CrtSetDbgFlag();
	static void MsgBoxAssert(EngineString ErrorMsg);
	static double CalculatePerformance(double t1,double t2);
};
