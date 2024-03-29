#include "Pre.h"
#include "EngineFile.h"

EngineFile::EngineFile()
{
}

EngineFile::EngineFile(std::string _Path)
{
	Path = _Path;
}

EngineFile::~EngineFile()
{
}

std::string EngineFile::GetFileName()
{
	return Path.filename().string();
}

std::string EngineFile::GetStringPath()
{
	return Path.string();
}
