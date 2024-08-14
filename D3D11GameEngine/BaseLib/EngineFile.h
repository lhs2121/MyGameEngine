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

enum class MoveMode
{
	Start,
	End,
};
class BaseAPI EngineFile 
{
public:
	EngineFile() = default;
	EngineFile(const char* _Path);
	~EngineFile();

	void SetPath(const char* _Path);
	EngineString GetPath();
	EngineString GetFileName();
	EngineString GetExt();
	void Open(FileMode _Mode);
	void Close();

	void ReadFileToMemory();
	void Move(const char* _TargetStr, MoveMode _Mode = MoveMode::Start);
	void MovePrev();
	void MoveNext();
	void SkipSpace();
	void ReWind();
	char GetChar();
	EngineString GetString(char _EndStr);

private:
	FILE* FilePtr = nullptr;
	char* FileStr = nullptr;
	char* CurFileStrPtr = nullptr;
	EngineString Path;
};

