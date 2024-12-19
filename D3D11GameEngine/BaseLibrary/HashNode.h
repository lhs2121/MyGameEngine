#pragma once
#include "EngineString.h"

struct HashNode
{
	HashNode* NextPtr = nullptr;
	EngineString Key;
	void* ItemPtr = nullptr;
};

struct IntHashNode
{
	IntHashNode* NextPtr = nullptr;
	int Key = -1;
	void* ItemPtr = nullptr;
};