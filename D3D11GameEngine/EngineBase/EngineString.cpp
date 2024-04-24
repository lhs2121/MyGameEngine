#include "Pre.h"
#include "EngineString.h"
#include <locale>
#include <codecvt>

EngineString::EngineString()
{
}

EngineString::~EngineString()
{
}

std::wstring EngineString::ToWideByteString(std::string& _String)
{
	wchar_t WideChar[256];

	MultiByteToWideChar(CP_ACP, 0, _String.c_str(), -1, WideChar, 256);
	
	std::wstring ResultString = WideChar;
	return ResultString;

}