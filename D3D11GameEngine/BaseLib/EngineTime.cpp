#include "Pre.h"
#include "EngineTime.h"

void EngineTime::Init()
{
	QueryPerformanceFrequency(&frequency);
}

void EngineTime::CountStart()
{
	QueryPerformanceCounter(&start);
}

float EngineTime::CountEnd()
{
	QueryPerformanceCounter(&end);
	float deltaTime = (end.QuadPart - start.QuadPart) / (float)frequency.QuadPart;
	return deltaTime;
}
