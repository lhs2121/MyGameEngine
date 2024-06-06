#include "Pre.h"
#include "EngineDebug.h"
#include <cassert>
EngineDebug::EngineDebug()
{
}

EngineDebug::~EngineDebug()
{
}

void EngineDebug::CrtSetBreakAlloc(UINT Number)
{
	_CrtSetBreakAlloc(Number);
}

void EngineDebug::CrtSetDbgFlag()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

void EngineDebug::MsgBoxAssert(EngineString ErrorMsg)
{
	MessageBox(nullptr, ErrorMsg.c_str(), "Error", MB_OK);
	assert(0);
}

