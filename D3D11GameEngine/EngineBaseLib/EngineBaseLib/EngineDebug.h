#pragma once
#include "EngineString.h"

class __declspec(dllexport) EngineDebug
{
public:
	// constrcuter destructer
	EngineDebug();
	~EngineDebug();

	//constrcuter destructer
	EngineDebug(const EngineDebug& _Other) = delete;
	EngineDebug(EngineDebug&& _Other) noexcept = delete;
	EngineDebug& operator=(const EngineDebug& _Other) = delete;
	EngineDebug& operator=(EngineDebug&& _Other) noexcept = delete;

	static void CrtSetBreakAlloc(UINT Number);
	static void CrtSetDbgFlag();
	static void MsgBoxAssert(EngineString ErrorMsg);

};

