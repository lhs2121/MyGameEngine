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

std::wstring EngineString::GetWideString(std::string& _String)
{
	int Length = MultiByteToWideChar(CP_ACP, 0, _String.c_str(), -1, nullptr, 0);
	wchar_t* WideChar = new wchar_t[Length];

	MultiByteToWideChar(CP_ACP, 0, _String.c_str(), -1, WideChar, Length);
	
	std::wstring ResultString = WideChar;

	if (WideChar != nullptr)
	{
		delete[] WideChar;
		WideChar = nullptr;
	}
	
	return ResultString;
}