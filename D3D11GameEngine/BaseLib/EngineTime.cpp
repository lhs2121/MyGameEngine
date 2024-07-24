#include "Pre.h"
#include "EngineTime.h"

void EngineTime::Init()
{
	QueryPerformanceFrequency(&Frequency);
}

void EngineTime::CountStart()
{
	QueryPerformanceCounter(&Start);
}

float EngineTime::CountEnd()
{
	QueryPerformanceCounter(&End);
	float DeltaTime = (End.QuadPart - Start.QuadPart) / (float)Frequency.QuadPart;
	return DeltaTime;
}
