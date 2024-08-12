#pragma once

struct HashNode;
struct IntHashNode;
class EngineString;
class BaseAPI EngineHashMap
{
public:
	bool      Add(EngineString _Key, void* ItemPtr);
	void*     Get(const char* _Key);
	UINT      Count();
	void      GoFirst();
	void      GoNext();
	void*     GetCurItem();

	~EngineHashMap();
private:
	int       Hash(const char* _Key) const;

	HashNode* Header = nullptr;
	HashNode* Array = nullptr;

	UINT       CurIndex = 0;
	UINT       ArraySize = 197;
	UINT       ElementCount = 0;
};

class BaseAPI EngineIntHashMap
{
public:
	bool      Add(UINT _Key, void* ItemPtr);
	void*     Get(UINT _Key);
	int       Count();
	void      GoFirst();
	void      GoNext();
	void*     GetCurItem() const;

	~EngineIntHashMap();
private:
	UINT       Hash(UINT _Key) const;

	IntHashNode* Header = nullptr;
	IntHashNode* Array = nullptr;

	UINT       CurIndex = 0;
	UINT       ArraySize = 197;
	UINT       ElementCount = 0;
};
