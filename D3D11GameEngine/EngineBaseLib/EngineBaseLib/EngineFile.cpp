#include "Pre.h"
#include "EngineFile.h"
#include "EngineDebug.h"
#include <filesystem>

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
		if (*(Header -1) == '\\')
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
	EngineString Mode;
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
	default:
		break;
	}

    fopen_s(&FilePtr, Path.c_str(), Mode.c_str());
	if (FilePtr == nullptr)
	{
		EngineDebug::MsgBoxAssert("파일을 여는데 실패했습니다");
	}
}

void EngineFile::Close()
{
	fclose(FilePtr);
}


