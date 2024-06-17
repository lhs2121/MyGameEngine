#include "Pre.h"
#include "EngineFile.h"
#include "EngineDebug.h"
#include <filesystem>

EngineString EngineFile::GetFileName()
{
	EngineString FimeName;
	std::filesystem::path stdPath = Path.c_str();
	FimeName = stdPath.filename().replace_extension("").string().c_str();
	return FimeName;
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

