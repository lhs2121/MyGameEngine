#include "Pre.h"
#include "EngineString.h"

EngineString::EngineString()
{
}

EngineString::~EngineString()
{
}

std::wstring EngineString::ToWideString(std::string _String)
{
	std::wstring Result;
	return Result.assign(_String.begin(), _String.end());
}

std::string EngineString::ToMultiString(std::wstring _WString)
{
	std::string Result;
	return Result.assign(_WString.begin(), _WString.end());
}
