#pragma once
#include "EnginePath.h"

enum class FileMode
{
	Read,
	Write,
	ReadBinary,
	WriteBinary,
};
class __declspec(dllexport) EngineFile : public EnginePath
{
public:
	// constrcuter destructer
	EngineFile();
	EngineFile(const char* _Path);

	~EngineFile();

	EngineString GetFileName();

	void Open(FileMode _Mode);
	void Close();

	FILE* FilePtr = nullptr; 
};

