#pragma once

class EngineKey
{
public:
	float KeyCode = -1;
	bool IsDown = false;
	bool IsPress = false;
	bool IsUp = false;
	bool IsFree = false;
};
class EngineInput
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

	void AllKeyInit();
	void AddKey(int KeyCode);

	void SetAllKeyState();

	bool IsDown(int KeyCode);
	bool IsPress(int KeyCode);
	bool IsUp(int KeyCode);
	bool IsFree(int KeyCode);

	std::vector<EngineKey> AllKey;
};

