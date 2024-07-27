#pragma once
#include "MediaAPI.h"

class EngineKey
{
public:
	int KeyCode = -1;
	bool IsDown = false;
	bool IsPress = false;
	bool IsUp = false;
	bool IsFree = false;
};
class EngineInput : public IEngineInput
{
public:
	EngineInput();
	~EngineInput();

	void CreateKey(int KeyCode) override;

	void Init() override;
	void SetAllKeyState() override;

	bool IsDown(int KeyCode) override;
	bool IsPress(int KeyCode) override;
	bool IsUp(int KeyCode) override;
	bool IsFree(int KeyCode) override;

	EngineIntHashMap AllKey;
};

