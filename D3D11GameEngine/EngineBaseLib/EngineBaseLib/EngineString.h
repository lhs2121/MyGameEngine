#pragma once

struct IEngineStaticMemoryPool;
class EngineAPI EngineString
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
		*this = OtherString.String;
	};
	EngineString(const EngineString& OtherString)
	{
		*this = OtherString.String;
	};
	bool operator<(const EngineString& other) const
	{
		return std::strcmp(String, other.String) < 0;
	}
	~EngineString();

	static void DeleteAllStringPool();
	static int GetByte(const char* OtherString);
	void GetUTF8(wchar_t** WideString);	
	const char* c_str();

	void operator=(EngineString& OtherString);
	void operator=(const char* OtherString);

	void operator+=(EngineString& OtherString);
	void operator+=(const char* OtherString);
	void operator+=(unsigned long long Num);

	bool operator==(EngineString& OtherString);
	bool operator==(const char* OtherString);

	bool operator!=(EngineString& OtherString);
	bool operator!=(const char* OtherString);
private:
	static void CreateAllStringPool();
	static IEngineStaticMemoryPool* GetStringPool(int ByteSize);

	static bool IsCreateStringPool;
	static IEngineStaticMemoryPool* StringPool16;
	static IEngineStaticMemoryPool* StringPool32;
	static IEngineStaticMemoryPool* StringPool64;
	static IEngineStaticMemoryPool* StringPool128;
	static IEngineStaticMemoryPool* StringPool256;
	static IEngineStaticMemoryPool* StringPool512;

	char* String = nullptr;
};

