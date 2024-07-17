#include "Pre.h"
#include "ContentsCore.h"
#include "TestLevel.h"
ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Awake()
{
	EngineCore::CreateLevel("TestLevel", new TestLevel());
	EngineCore::ChangeLevel("TestLevel");
}

void ContentsCore::Start()
{
	EngineCore::CreateLevel("TestLevel",new TestLevel());
	EngineCore::ChangeLevel("TestLevel");
}
