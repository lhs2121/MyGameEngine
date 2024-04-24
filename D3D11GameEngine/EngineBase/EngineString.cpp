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
	wchar_t strUnicode[256] = { 0, };
	char strMultibyte[256] = { 0, };
	wcscpy_s(strUnicode, 256, L"유니코드");
	int len = WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, strMultibyte, len, NULL, NULL);
}