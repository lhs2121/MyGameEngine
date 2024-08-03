#pragma once

struct HashNode;
struct IntHashNode;
class EngineString;
class BaseAPI EngineHashMap
{
public:
	bool      Add(EngineString _Key, void* ItemPtr);
	void*     Get(const char* _Key);
	int       Count();
	void      GoFirst();
	void      GoNext();
	void*     GetCurItem();

private:
	int       Hash(const char* _Key) const;

	HashNode* Header = nullptr;
	HashNode* End = nullptr;
	HashNode* Array = nullptr;

	UINT CurIndex = 0;
	int       ArraySize = 197;
	int       ElementCount = 0;
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
	IntHashNode* End = nullptr;
	IntHashNode* Array = nullptr;
	int       ArraySize = 197;
	int       ElementCount = 0;
};
