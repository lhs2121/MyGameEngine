#include "Windows.h"
#include <string>
#include <map>
#include <vector>
#include <EngineBaseLib\EngineBaseLib\EngineBaseInterface.h>
#pragma comment(lib,"EngineBaseLib.lib")


void func(EngineString& String)
{
	String += "a";
}
void func2(std::string& String)
{
	String += "a";
}
int main()
{
	EngineString a;
	func(a);
	std::string b;
	func2(b);
	
}
