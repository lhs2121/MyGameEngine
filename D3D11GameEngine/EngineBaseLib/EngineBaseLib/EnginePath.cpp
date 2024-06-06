#include "Pre.h"
#include "EnginePath.h"

EnginePath::EnginePath(EngineString _Path)
{
	Path = _Path;
}

EngineString EnginePath::GetPath()
{
	return Path;
}