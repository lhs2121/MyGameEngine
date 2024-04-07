#include "Pre.h"
#include "ContentsCore.h"
#include "TestLevel.h"
ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	EngineLevel::CreateLevel<TestLevel>("TestLevel");
}
