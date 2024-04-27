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


	static void CreateKey(int KeyCode);

	static void InitAllKey();
	static void DeleteAllKey();

	static void SetAllKeyState();

	static bool IsDown(int KeyCode);
	static bool IsPress(int KeyCode);
	static bool IsUp(int KeyCode);
	static bool IsFree(int KeyCode);
	
	static std::map<int,EngineKey*> AllKey;
};

