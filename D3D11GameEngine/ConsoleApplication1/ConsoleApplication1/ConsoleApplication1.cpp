#include <iostream>
#include <cstring>
#include <chrono>
#include <Windows.h>
#include <string>
#include <EngineBaseLib\EngineBaseLib\EngineBaseInterface.h>

int main()
{
	int a[2][2][2] = { {1,2,3,4},{5,6,7,8} };
	
	int(*ap)[2][2] = a;

	int* b = ap[0][1];
}