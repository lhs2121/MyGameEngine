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

double EngineDebug::CalculatePerformance(double t1, double t2)
{
    if (t1 <= 1.0E-6)
    {
        t1 = 0.0;
    }
    if (t2 <= 1.0E-6)
    {
        t2 = 0.0;
    }

    if (t1 == 0.0f || t2 == 0.0f)
    {
        OutputDebugStringA("������ ����ð��� 0�� �ſ� ������ ������ �ߴ��մϴ�.\n");
        return 0.0f;
    }

    double Diff = 0.0;

    Diff = (abs(t1 - t2) / t1) * 100;
    
    EngineString Message;

    if (t1 < t2)
    {
        Message = "ù��° �Լ��� ";
    }
    if (t1 > t2)
    {
        Message = "�ι�° �Լ��� ";
    }
    Message += Diff;
    Message += "%��ŭ ������ �����ϴ�.\n";

    OutputDebugStringA(Message.c_str());
    return Diff;
}

