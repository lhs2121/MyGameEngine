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
	Front,
	Back
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
	void Move(const char* _TargetStr, MoveMode _Mode = MoveMode::Front);
	void MoveFront();
	void MoveBack();
	void ReWind();
	EngineString GetString(char _EndStr, int _Offset = 0);

private:
	FILE* FilePtr = nullptr;
	char* FileStr = nullptr;
	char* CurFileStrPtr = nullptr;
	EngineString Path;
};

