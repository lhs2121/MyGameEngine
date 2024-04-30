#pragma once

struct IEngineInput
{
	virtual void CreateKey(int KeyCode) = 0;

	virtual void InitAllKey() = 0;
	virtual void DeleteAllKey() = 0;

	virtual void SetAllKeyState() = 0;

	virtual bool IsDown(int KeyCode) = 0;
	virtual bool IsPress(int KeyCode) = 0;
	virtual bool IsUp(int KeyCode) = 0;
	virtual bool IsFree(int KeyCode) = 0;
};

extern "C" __declspec(dllexport) void CreateInput(IEngineInput** ppIEngineInput);