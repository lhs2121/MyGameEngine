#include "Pre.h"
#include "EngineFile.h"
#include <filesystem>
EngineFile::EngineFile()
{
}

EngineFile::EngineFile(const char* _Path)
{
	Path = _Path;
}

EngineFile::~EngineFile()
{
}

EngineString EngineFile::GetFileName()
{
	std::filesystem::path stdPath = Path.c_str();
	return stdPath.filename().replace_extension("").string().c_str();
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
		EngineDebug::MsgBoxAssert("������ ���µ� �����߽��ϴ�");
	}
}

void EngineFile::Close()
{
	fclose(FilePtr);
}

