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
	void UpdateKeyStates() override;

	bool IsDown(int KeyCode, void* _UserPtr) override;
	bool IsPress(int KeyCode, void* _UserPtr) override;
	bool IsUp(int KeyCode, void* _UserPtr) override;
	bool IsFree(int KeyCode, void* _UserPtr) override;

	void AddUser(void* _UserPtr) override;
	EngineIntHashMap AllKey;
	std::vector<void*> Users;
};

