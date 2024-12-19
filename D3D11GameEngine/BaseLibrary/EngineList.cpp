#include "pch.h"
#include "EngineList.h"

void EngineList::Add(void* _ItemPtr)
{
	Count++;
	if (FirstNode == nullptr)
	{
		FirstNode = new Node();
		FirstNode->ItemPtr = _ItemPtr;

		CurNode = FirstNode;
		return;
	}

	Node* NewNode = new Node();
	NewNode->ItemPtr = _ItemPtr;

	Node* CurTail = FirstNode;
	while (true)
	{
		if (CurTail->NextPtr == nullptr)
		{
			break;
		}

		CurTail = CurTail->NextPtr;
	}

	CurTail->NextPtr = NewNode;
	NewNode->PrevPtr = CurTail;
}

void EngineList::Delete(void* _TargetPtr)
{
	GoFirst();
	for (int i = 0; i < Count; i++)
	{
		if (CurNode->ItemPtr == _TargetPtr)
		{
			DeleteCurNode();
			break;
		}
		GoNext();
	}
}

void EngineList::DeleteCurNode()
{
	if (CurNode != nullptr)
	{
		Node* PrevNode = CurNode->PrevPtr;
		Node* NextNode = CurNode->NextPtr;

		if (NextNode != nullptr)
		{
			NextNode->PrevPtr = PrevNode;
		}

		if (PrevNode != nullptr)
		{
			PrevNode->NextPtr = NextNode;
		}

		Count--;
		delete CurNode; 
		CurNode = FirstNode;
	}
}

void EngineList::GoPrev()
{
	if (CurNode->PrevPtr != nullptr)
	{
		CurNode = CurNode->PrevPtr;
	}
}

void EngineList::GoNext()
{
	if (CurNode->NextPtr != nullptr)
	{
		CurNode = CurNode->NextPtr;
	}
}

int EngineList::GetCount()
{
	return Count;
}

void EngineList::GoFirst()
{
	if (FirstNode != nullptr)
	{
		CurNode = FirstNode;
	}
}

void* EngineList::Item() const
{
	if (CurNode == nullptr)
	{
		return nullptr;
	}

	return CurNode->ItemPtr;
}

EngineList::EngineList()
{
}

EngineList::~EngineList()
{
	GoFirst();
	while (true)
	{
		if (CurNode == nullptr)
		{
			break;
		}

		Node* NextNode = CurNode->NextPtr;
		delete CurNode;
		CurNode = NextNode;
	}
}
