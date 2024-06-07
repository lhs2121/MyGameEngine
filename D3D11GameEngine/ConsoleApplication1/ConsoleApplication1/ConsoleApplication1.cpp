#include <..\EngineBaseLib\IEngineBase.h>
#include <..\EngineBaseLib\EngineDirectory.h>
#include <..\EngineBaseLib\EngineFile.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <string>
#pragma comment(lib,"EngineBaseLib.lib")



void a(std::string str)
{
	str += "asd";
}
void b(EngineString str)
{
	str += "asd";
}
int main()
{
	a("asd");
	b("asd");
	EngineDirectory dir;
	dir.GoBase();
 	EngineDirectory dir2;
}