#include "Pre.h"
#include "EngineFile.h"
#include "EngineDebug.h"

EngineFile::EngineFile(const char* _Path)
{
	Path = _Path;
}

EngineFile::~EngineFile()
{
	if (FileStr != nullptr)
	{
		delete[] FileStr;
		FileStr = nullptr;
	}
}
EngineString EngineFile::GetFileName()
{
	int ByteSize = EngineString::GetByte(Path.String);

	int ExtByteSize = EngineString::GetByte(GetExt().c_str());

	char* temp = new char[ByteSize];
	memcpy_s(temp, ByteSize, Path.String, ByteSize);
	char* Header = Path.String;
	Header += ByteSize;
	while (true)
	{
		if (*(Header - 1) == '\\')
		{
			break;
		}
		Header--;
	}
	__int64 WasteSize = Header - Path.String;
	memset(temp, 0, WasteSize);
	memset(temp + ByteSize - ExtByteSize, 0, ExtByteSize);
	char* temp2 = temp + WasteSize;

	EngineString Result = temp2;

	delete[] temp;

	return Result;
}

EngineString EngineFile::GetExt()
{
	char* Temp = Path.String;
	int ByteSize = EngineString::GetByte(Path.String);

	Temp += ByteSize;
	while (true)
	{
		Temp -= 1;
		if (*Temp == '.')
		{
			return Temp;
		}
	}

}

void EngineFile::SetPath(const char* _Path)
{
	Path = _Path;
}

EngineString EngineFile::GetPath()
{
	return Path.c_str();
}

void EngineFile::Open(FileMode _Mode)
{
	const char* Mode = nullptr;
	switch (_Mode)
	{
	case FileMode::Read:
		Mode = "r";
		break;
	case FileMode::Write:
		Mode = "w";
		break;
	case FileMode::ReadBinary:
		Mode = "rb";
		break;
	case FileMode::WriteBinary:
		Mode = "wb";
		break;
	}

	fopen_s(&FilePtr, Path.c_str(), Mode);
	if (FilePtr == nullptr)
	{
		EngineDebug::MsgBoxAssert("파일을 여는데 실패했습니다");
	}
}

void EngineFile::Close()
{
	fclose(FilePtr);
	FilePtr = nullptr;
}

void EngineFile::ReadFileToMemory()
{
	bool OpenHere = false;
	if (FilePtr == nullptr)
	{
		Open(FileMode::Read);
		OpenHere = true;
	}
	fseek(FilePtr, 0, SEEK_END);
	UINT FileLen = ftell(FilePtr);
	rewind(FilePtr);

	FileStr = new char[FileLen];
	fread(FileStr, sizeof(char), FileLen, FilePtr);
	CurFileStrPtr = FileStr;
	if (OpenHere)
	{
		Close();
	}

}

void EngineFile::Move(const char* _TargetStr, MoveMode _Mode)
{
	if (FileStr == nullptr)
	{
		EngineDebug::MsgBoxAssert("먼저 ReadFileToMemory()을 호출해주세요");
	}

	CurFileStrPtr = strstr(CurFileStrPtr, _TargetStr);
	if (CurFileStrPtr == 0)
	{
		EngineDebug::MsgBoxAssert("파일안에서 문자열을 못찾았습니다");
	}

	if (_Mode == MoveMode::End)
	{
		size_t len = strlen(_TargetStr) - 1;
		CurFileStrPtr += len;
	}
}

void EngineFile::MovePrev()
{
	CurFileStrPtr--;
}

void EngineFile::MoveNext()
{
	CurFileStrPtr++;
}

char EngineFile::GetChar()
{
	return *CurFileStrPtr;
}

void EngineFile::SkipSpace()
{
	while (' ' == *CurFileStrPtr)
	{
		CurFileStrPtr++;
	}
}

void EngineFile::ReWind()
{
	CurFileStrPtr = FileStr;
}

EngineString EngineFile::GetString( char _EndStr)
{
	if (FileStr == nullptr)
	{
		EngineDebug::MsgBoxAssert("먼저 ReadFileToMemory()을 호출해주세요");
	}
	UINT _StrCount = 0;
	char* temp = CurFileStrPtr;
	while (_EndStr != *temp++)
	{
		_StrCount++;
	}
	char* str = new char[_StrCount + 1];
	memcpy_s(str, _StrCount, CurFileStrPtr, _StrCount);
	str[_StrCount] = '\0';
	EngineString Result = str;
	return Result;
}


