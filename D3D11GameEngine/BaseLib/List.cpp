#include "List.h"
#include <list>
List::~List()
{
}

void List::Add(int _Size,void* NewPtr)
{
	Node* CurNode = FirstNode;
	while (true)
	{
		if (CurNode == nullptr)
		{
			break;
		}

		CurNode = CurNode->NextPtr;
	}

	CurNode = new Node();
	CurNode->ObjectPtr = malloc(_Size);
	memcpy_s(CurNode->ObjectPtr, _Size, NewPtr, _Size);

	Node* PrevNode = CurNode->PrevPtr;
	if (PrevNode != nullptr)
	{
		PrevNode->NextPtr = CurNode;
		CurNode->PrevPtr = PrevNode;
	}
}

void List::Delete(int _Index)
{
	Node* CurNode = FirstNode;

	for (int i = 0; i < _Index; i++)
	{
		if (CurNode == nullptr)
		{
			return;
		}

		CurNode = CurNode->NextPtr;
	}

	if (CurNode != nullptr)
	{
		delete CurNode;
	}

}

Node::~Node()
{
	free(ObjectPtr);
}
