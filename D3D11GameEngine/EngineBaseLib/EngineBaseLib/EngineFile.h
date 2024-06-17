#pragma once
#include "EngineString.h"

struct _iobuf;
typedef struct _iobuf FILE;

enum class FileMode
{
	Read,
	Write,
	ReadBinary,
	WriteBinary,
};

class EngineAPI EngineFile 
{
public:
	void SetPath(const char* _Path);
	EngineString GetPath();
	EngineString GetFileName();
	void Open(FileMode _Mode);
	void Close();

private:
	FILE* FilePtr = nullptr;
	EngineString Path;
};

