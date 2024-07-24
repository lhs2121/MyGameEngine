#include "Pre.h"
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
