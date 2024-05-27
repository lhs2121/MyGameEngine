#pragma once

class __declspec(dllexport) EngineString
{
public:
	// constrcuter destructer
	EngineString();
	EngineString(const char* OtherString)
	{
		*this = OtherString;
	};
	~EngineString();

	void operator=(EngineString& OtherString);
	void operator=(const char* OtherString);


	void GetUTF8(wchar_t** WideString);
	static int GetByte(const char* OtherString);
	
	const char* c_str();
	int GetByte();
	int GetLen() const;
	
	void operator+=(EngineString& OtherString);
	void operator+=(const char* OtherString);

private:
	static void* FirstString16;
	static void* FirstString32;
	static void* FirstString64;
	
	char* String = nullptr;
};

