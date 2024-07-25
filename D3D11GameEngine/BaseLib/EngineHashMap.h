#pragma once

struct HashNode;
struct IntHashNode;
class BaseAPI EngineHashMap
{
public:
	bool      Add(const char* _Key, void* ItemPtr);
	void*     Get(const char* _Key);

private:
	int       Hash(const char* _Key) const;

	HashNode* Array = nullptr;
	int       ArraySize = 127;
};

class BaseAPI EngineIntHashMap
{
public:
	bool      Add(int _Key, void* ItemPtr);
	void*     Get(int _Key);
	int       Count();
	void      GoFirst();
	void      GoNext();
	void*     GetCurItem();

private:
	int       Hash(int _Key) const;

	IntHashNode* Header = nullptr;
	IntHashNode* Array = nullptr;
	int       ArraySize = 197;
	int       ElementCount = 0;
};
