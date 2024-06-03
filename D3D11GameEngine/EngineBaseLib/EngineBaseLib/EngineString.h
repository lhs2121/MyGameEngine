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

	static int GetByte(const char* OtherString);
	static EngineMemoryPool* GetStringPool(int ByteSize);

	

	void operator=(EngineString& OtherString);
	void operator=(const char* OtherString);
	void operator+=(EngineString& OtherString);
	void operator+=(const char* OtherString);

	void GetUTF8(wchar_t** WideString);	
	const char* c_str();
private:
	static EngineMemoryPool StringPool16;
	static EngineMemoryPool StringPool32;
	static EngineMemoryPool StringPool64;





	char* String = nullptr;
};

