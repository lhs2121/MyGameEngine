#pragma once

struct HashNode
{
	HashNode* NextPtr = nullptr;
	const char* Key = nullptr;
	void* ItemPtr = nullptr;
};
class BaseAPI EngineHashMap
{
public:
	bool      Add(const char* _Key, void* ItemPtr);
	void*     Get(const char* _Key);

	HashNode* Array = nullptr;
	int       ArraySize = 100;

private:
	int       Hash(const char* _Key) const;
};