#include <iostream>
#include <cstring>
#include <chrono>
#include <Windows.h>
#include <string>
#include <EngineBaseLib\EngineBaseLib\EngineBaseInterface.h>
#pragma comment(lib,"EngineBaseLib.lib")

int main()
{
	EngineString a = "asdf";
	a += 123;
}