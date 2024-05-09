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

std::string EngineString::GetMultiString(std::wstring& WideString)
{
	int Length = WideCharToMultiByte(CP_ACP, 0, WideString.c_str(), -1, nullptr, 0, nullptr, nullptr);
	char* CharBuffer = new char[Length];

	WideCharToMultiByte(CP_ACP, 0, WideString.c_str(), -1, CharBuffer, Length, nullptr, nullptr);

	std::string ResultString = CharBuffer;
	if (CharBuffer != nullptr)
	{
		delete[] CharBuffer;
		CharBuffer = nullptr;
	}

	return ResultString;
}

std::wstring EngineString::GetWideString(std::string& String)
{
	int Length = MultiByteToWideChar(CP_ACP, 0, String.c_str(), -1, nullptr, 0);
	wchar_t* WideCharBuffer = new wchar_t[Length];

	MultiByteToWideChar(CP_ACP, 0, String.c_str(), -1, WideCharBuffer, Length);
	
	std::wstring ResultString = WideCharBuffer;
	if (WideCharBuffer != nullptr)
	{
		delete[] WideCharBuffer;
		WideCharBuffer = nullptr;
	}
	
	return ResultString;
}