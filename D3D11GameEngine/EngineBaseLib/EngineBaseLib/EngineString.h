#pragma once

struct IEngineMemoryPool;
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
	void operator+=(int Num);
	void operator+=(float Num);

	bool operator==(EngineString& OtherString);
	bool operator==(const char* OtherString);

	bool operator!=(EngineString& OtherString);
	bool operator!=(const char* OtherString);
private:
	static void CreateAllStringPool();
	static IEngineMemoryPool* GetStringPool(int ByteSize);

	static bool IsCreateStringPool;
	static IEngineMemoryPool* StringPool16;
	static IEngineMemoryPool* StringPool32;
	static IEngineMemoryPool* StringPool64;
	static IEngineMemoryPool* StringPool128;
	static IEngineMemoryPool* StringPool256;
	static IEngineMemoryPool* StringPool512;

	char* String = nullptr;
};

