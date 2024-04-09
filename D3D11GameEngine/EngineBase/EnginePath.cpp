#include "Pre.h"
#include "EnginePath.h"

EnginePath::EnginePath()
{
}

EnginePath::EnginePath(std::string _Path)
{
	_Path = _Path;
}

EnginePath::~EnginePath()
{
}

std::string EnginePath::GetStringPath()
{
	std::string StringPath = Path.string();
	return StringPath;
}