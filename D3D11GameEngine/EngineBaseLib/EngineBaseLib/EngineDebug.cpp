#include "Pre.h"
#include "EngineDebug.h"
#include <cassert>

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

double EngineDebug::CalculateTime(std::function<void()> ExecuteTarget, int ExecuteCount, const char* FunctionName)
{
    clock_t Start; 
    clock_t End;
    double Time;

    Start = clock();
    for (size_t i = 0; i < ExecuteCount; i++)
    {
        ExecuteTarget();
    }
    End = clock();

    Time = ((double)(End - Start)) / CLOCKS_PER_SEC;

    EngineString Message = FunctionName;
    Message += " 함수 실행결과 :";
    Message += Time;
    Message += "초 소요.\r\n";

    OutputDebugStringA(Message.c_str());
    return Time;
}
