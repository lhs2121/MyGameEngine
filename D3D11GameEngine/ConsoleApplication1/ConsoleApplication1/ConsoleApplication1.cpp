#include <iostream>
#include <cstring>
#include <chrono>
#include <Windows.h>
#include <string>
#include <EngineBaseLib\EngineBaseLib\EngineBaseInterface.h>

int main()
{
	int** pp = new int*[5];

	for (size_t i = 0; i < 5; i++)
	{
		pp[i] = new int[5];
	}

	pp[0][0] = 0;
	pp[0][1] = 1;
	pp[0][2] = 2;
	pp[0][3] = 2;
	pp[0][4] = 2;
	pp[0][155] = 2;

	
	__int64 ptr = (__int64)pp[0];

}