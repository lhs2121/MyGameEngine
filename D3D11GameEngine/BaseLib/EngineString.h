#pragma once

struct IEngineStaticPool;
class BaseAPI EngineString
{
	friend class EngineFile;
public:
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
	bool operator<(const EngineString& other) const;
	~EngineString();

	static void DeleteAllStringPool();
	static int GetByte(const char* OtherString);
	void GetUTF8(wchar_t** WideString);	
	const char* c_str();

	void operator=(EngineString& OtherString);
	void operator=(const char* OtherString);

	void operator+=(EngineString& OtherString);
	void operator+=(const char* OtherString);
	void operator+=(double Num);

	bool operator==(EngineString& OtherString);
	bool operator==(const char* OtherString);

	bool operator!=(EngineString& OtherString);
	bool operator!=(const char* OtherString);
private:
	static void CreateAllStringPool();
	static IEngineStaticPool* GetStringPool(int ByteSize);

	static bool IsCreateStringPool;
	static IEngineStaticPool* StringPool16;
	static IEngineStaticPool* StringPool32;
	static IEngineStaticPool* StringPool64;
	static IEngineStaticPool* StringPool128;
	static IEngineStaticPool* StringPool256;
	static IEngineStaticPool* StringPool512;

	char* String = nullptr;
};

