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

class EngineFile : public IEngineFile
{
public:
	void SetPath(const char* _Path) override;
	const char* GetFileName() override;
	void Open(FileMode _Mode) override;
	void Close() override;

private:
	FILE* FilePtr = nullptr;
	EngineString Path;
};

