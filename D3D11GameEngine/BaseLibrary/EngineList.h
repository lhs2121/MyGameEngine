#pragma once
#include "Interface.h"

struct Node
{
	void* ItemPtr = nullptr;
	Node* PrevPtr = nullptr;
	Node* NextPtr = nullptr;
};
class BASELIBRARY_API EngineList
{
public:
	void  Add(void* _ItemPtr);
	void  Delete(void* _TargetPtr);
	void  DeleteCurNode();

	void  GoFirst();
	void  GoPrev();
	void  GoNext();
	int   GetCount();
	void* Item() const;

	EngineList();
	~EngineList();
private:
	Node* FirstNode = nullptr;
	Node* CurNode = nullptr;

	int Count = 0;
};