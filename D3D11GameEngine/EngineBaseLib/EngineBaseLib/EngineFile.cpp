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

