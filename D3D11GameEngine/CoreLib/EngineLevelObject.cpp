#include "Pre.h"
#include "EngineLevelObject.h"
#include "EngineLevel.h"

EngineLevel* EngineLevelObject::GetLevel()
{
	return (EngineLevel*)GetTopParent();
}
