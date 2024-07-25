#pragma once


struct HashNode
{
	HashNode* NextPtr = nullptr;
	const char* Key = nullptr;
	void* ItemPtr = nullptr;
};

struct IntHashNode
{
	IntHashNode* NextPtr = nullptr;
	int Key = -1;
	void* ItemPtr = nullptr;
};