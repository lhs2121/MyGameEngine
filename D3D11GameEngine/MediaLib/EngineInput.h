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

class EngineInput
{
public:
	EngineInput()
	{
		mainInput = this;
		Users.reserve(100);
	}
	~EngineInput();

	static EngineInput* mainInput;

	void CreateKey(int KeyCode);

	void Init();
	void UpdateKeyStates();

	bool IsDown(int KeyCode, void* _UserPtr);
	bool IsPress(int KeyCode, void* _UserPtr);
	bool IsUp(int KeyCode, void* _UserPtr);
	bool IsFree(int KeyCode, void* _UserPtr);

	void AddUser(void* _UserPtr);

	EngineIntHashMap AllKey;
	std::vector<void*> Users;
};

