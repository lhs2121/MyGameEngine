#include "Pre.h"
#include "HashNode.h"
#include "EngineHashMap.h"
#include "EngineString.h"
#include <string>

bool EngineHashMap::Add(EngineString _Key, void* ItemPtr)
{
	ElementCount++;

	if (Array == nullptr)
	{
		Array = new HashNode[ArraySize];
		End = &Array[ArraySize - 1];
	}
	int Index = Hash(_Key.c_str());

	HashNode* CurNode = &Array[Index];

	if (CurNode->ItemPtr == nullptr)
	{
		CurNode->Key = _Key;
		CurNode->ItemPtr = ItemPtr;
		return true;
	}

	while (true)
	{
		if (CurNode->Key == _Key)
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
		if (CurNode->Key == _Key)
		{
			break;
		}

		CurNode = CurNode->NextPtr;
	}

	return CurNode->ItemPtr;
}

int EngineHashMap::Count()
{
	return ElementCount;
}

void EngineHashMap::GoFirst()
{
	for (size_t i = 0; i < ArraySize; i++)
	{
		if (Array[i].Key != 0)
		{
			CurIndex = i;
			Header = &Array[CurIndex];
			break;
		}
	}
}

void EngineHashMap::GoNext()
{
	int a = End - Header;
	if (Header->NextPtr != nullptr)
	{
		Header = Header->NextPtr;
		return;
	}

	while (true)
	{
		if (&Array[CurIndex] >= End)
		{
			return;
		}

		CurIndex++;
		Header = &Array[CurIndex];

		if (Header->Key != nullptr)
		{
			break;
		}
	}
}

void* EngineHashMap::GetCurItem()
{
	return Header->ItemPtr;
}

int EngineHashMap::Hash(const char* _Key) const
{
	unsigned long hash = 5381;
	int c = 0;
	int i = 0;
	while (_Key[i] != '\0')
	{
		c = _Key[i];
		hash = (((hash << 5) + hash) + c) % ArraySize;
		i++;
	}
	int Index = hash % ArraySize;

	return Index;
}

bool EngineIntHashMap::Add(int _Key, void* ItemPtr)
{
	if (Array == nullptr)
	{
		Array = new IntHashNode[ArraySize];
		End = &Array[ArraySize - 1];
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
		if (Header >= End)
		{
			return;
		}

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
