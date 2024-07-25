#include "Pre.h"
#include "HashNode.h"
#include "EngineHashMap.h"
#include <string>

bool EngineHashMap::Add(const char* _Key, void* ItemPtr)
{
	if (Array == nullptr)
	{
		Array = new HashNode[ArraySize];
	}

	int Index = Hash(_Key);

	HashNode* CurNode = &Array[Index];

	if (CurNode->ItemPtr == nullptr)
	{
		CurNode->Key = _Key;
		CurNode->ItemPtr = ItemPtr;
		return true;
	}

	while (true)
	{
		if (strcmp(CurNode->Key, _Key) == 0)
		{
			return false;	
		}

		if (CurNode->NextPtr == nullptr)
		{
			HashNode* NewNode = new HashNode();
			NewNode->ItemPtr = ItemPtr;
			NewNode->Key = _Key;

			CurNode->NextPtr = NewNode;
			return true;
		}
		
		CurNode = CurNode->NextPtr;
	}
	
}

void* EngineHashMap::Get(const char* _Key)
{
	int Index = Hash(_Key);
	HashNode* CurNode = &Array[Index];
	while (true)
	{
		if (strcmp(CurNode->Key, _Key) == 0)
		{
			break;
		}

		CurNode = CurNode->NextPtr;
	}

	return CurNode->ItemPtr;
}

int EngineHashMap::Hash(const char* _Key) const
{
	int IntKey = 0;
	char* c = (char*)_Key;
	while (*c != '\0')
	{
		IntKey += (int)*c;
		c++;
	}
	int Index = IntKey % ArraySize;

	return Index;
}

bool EngineIntHashMap::Add(int _Key, void* ItemPtr)
{
	if (Array == nullptr)
	{
		Array = new IntHashNode[ArraySize];
		IntHashNode* Node = &Array[90];
		int a = 0;
	}

	int Index = Hash(_Key);

	IntHashNode* CurNode = &Array[Index];

	if (CurNode->ItemPtr == nullptr)
	{
		CurNode->Key = _Key;
		CurNode->ItemPtr = ItemPtr;
	    ElementCount++;

		return true;
	}

	while (true)
	{
		if (CurNode->Key != _Key)
		{
			return false;
		}

		if (CurNode->NextPtr == nullptr)
		{
			IntHashNode* NewNode = new IntHashNode();
			NewNode->ItemPtr = ItemPtr;
			NewNode->Key = _Key;

			CurNode->NextPtr = NewNode;
			ElementCount++;
			return true;
		}

		CurNode = CurNode->NextPtr;
	}
}

void* EngineIntHashMap::Get(int _Key)
{
	int Index = Hash(_Key);
	IntHashNode* CurNode = &Array[Index];
	while (true)
	{
		if (CurNode->Key == _Key)
		{
			break;
		}

		CurNode = CurNode->NextPtr;
	}

	return CurNode->ItemPtr;
}

int EngineIntHashMap::Count()
{
	return ElementCount;
}

void EngineIntHashMap::GoFirst()
{
	for (size_t i = 0; i < ArraySize; i++)
	{
		if (Array[i].Key != -1)
		{
			Header = &Array[i];
			break;
		}
	}
}

void EngineIntHashMap::GoNext()
{
	if (Header->NextPtr != nullptr)
	{
		Header = Header->NextPtr;
		return;
	}

	while (true)
	{
		Header++;

		if (Header->Key != -1)
		{
			break;
		}
	}
}

void* EngineIntHashMap::GetCurItem()
{
	return Header->ItemPtr;
}

int EngineIntHashMap::Hash(int _Key) const
{
	int Result = 0;

	if (_Key > ArraySize)
	{
		Result = _Key % ArraySize;
	}
	else
	{
		Result = _Key;
	}

	return Result;
}
