#pragma once

class EngineMemoryPool;
class __declspec(dllexport) EngineString
{
public:
	// constrcuter destructer
	EngineString();
	EngineString(const char* OtherString)
	{
		*this = OtherString;
	};
	EngineString(EngineString& OtherString)
	{
		*this = OtherString.c_str();
	};
	~EngineString();

	void operator=(EngineString& OtherString);
	void operator=(const char* OtherString);
	void operator+=(EngineString& OtherString);
	void operator+=(const char* OtherString);


	void GetUTF8(wchar_t** WideString);
	static int GetByte(const char* OtherString);
	
	const char* c_str();
	int GetByte();
	int GetLen() const;

	static EngineMemoryPool StringPool16;
	static EngineMemoryPool StringPool32;
	static EngineMemoryPool StringPool64;

private:
	char* String = nullptr;
};

