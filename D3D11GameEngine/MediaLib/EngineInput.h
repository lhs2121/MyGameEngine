#pragma once
#include "MediaAPI.h"
#include <map>

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
	// constrcuter destructer
	EngineInput();
	~EngineInput();

	//constrcuter destructer
	EngineInput(const EngineInput& _Other) = delete;
	EngineInput(EngineInput&& _Other) noexcept = delete;
	EngineInput& operator=(const EngineInput& _Other) = delete;
	EngineInput& operator=(EngineInput&& _Other) noexcept = delete;


	void CreateKey(int KeyCode) override;

	void InitAllKey() override;
	void DeleteAllKey() override;

	void SetAllKeyState() override;

	bool IsDown(int KeyCode) override;
	bool IsPress(int KeyCode) override;
	bool IsUp(int KeyCode) override;
	bool IsFree(int KeyCode) override;

	static std::map<int,EngineKey*> AllKey;
};

