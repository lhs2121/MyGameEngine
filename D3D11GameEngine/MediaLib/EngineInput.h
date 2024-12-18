#pragma once
#include "interface.h"

class EngineKey
{
public:
	bool isDown = false;
	bool isPress = false;
	bool isUp = false;
	bool isFree = false;
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

	void CreateKey(int _keyCode);

	void Init();
	void UpdateKeyStates();

	bool IsDown(int _keyCode, void* _userPtr);
	bool IsPress(int _keyCode, void* _userPtr);
	bool IsUp(int _keyCode, void* _userPtr);
	bool IsFree(int _keyCode, void* _userPtr);

	void AddUser(void* _UserPtr);

	std::unordered_map<int,EngineKey*> allKey;
	std::vector<void*> Users;
};

