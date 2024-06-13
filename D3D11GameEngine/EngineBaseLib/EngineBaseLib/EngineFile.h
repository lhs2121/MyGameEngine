#pragma once
#include "EnginePath.h"
struct _iobuf;
typedef struct _iobuf FILE;

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

private:
	FILE* FilePtr = nullptr;
};

