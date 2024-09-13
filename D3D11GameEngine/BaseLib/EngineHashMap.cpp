#include "Pre.h"
#include "HashNode.h"
#include "BaseAPI.h"
#include "EngineHashMap.h"
#include "EngineString.h"
#include <string>

EngineHashMap::~EngineHashMap()
{
	for (size_t i = 0; i < ArraySize; i++)
	{
		HashNode* CurNode = &Array[i];

		if (CurNode->Key == nullptr)
		{
			continue;
		}

		HashNode* PrevNode = nullptr;
		while (true)
		{
			if (CurNode->NextPtr != nullptr)
			{
				PrevNode = CurNode;
				CurNode = CurNode->NextPtr;
			}
			else
			{
				if (CurNode != &Array[i])
				{
					PrevNode->NextPtr = nullptr;
					delete CurNode;
					CurNode = PrevNode;
				}
				else
				{
					break;
				}
			}
		}
	}
	if (Array != nullptr)
	{
		delete[] Array;
		Array = nullptr;
	}
	
}

EngineIntHashMap::~EngineIntHashMap()
{
	for (size_t i = 0; i < ArraySize; i++)
	{
		IntHashNode* CurNode = &Array[i];

		if (CurNode->Key == -1)
		{
			continue;
		}

		IntHashNode* PrevNode = nullptr;
		while (true)
		{
			if (CurNode->NextPtr != nullptr)
			{
				PrevNode = CurNode;
				CurNode = CurNode->NextPtr;
			}
			else
			{
				if (CurNode != &Array[i])
				{
					PrevNode->NextPtr = nullptr;
					delete CurNode;
					CurNode = PrevNode;
				}
				else
				{
					break;
				}
			}
		}
	}
	if (Array != nullptr)
	{
		delete[] Array;
		Array = nullptr;
	}
}

bool EngineHashMap::Add(EngineString _Key, void* ItemPtr)
{
	if (Array == nullptr)
	{
		Array = new HashNode[ArraySize];
	}
	int Index = Hash(_Key.c_str());

	HashNode* CurNode = &Array[Index];

	if (CurNode->ItemPtr == nullptr)
	{
		CurNode->Key = _Key;
		CurNode->ItemPtr = ItemPtr;

		ElementCount++;
		return true;
	}

	while (true)
	{
		if (CurNode->Key == _Key)
		{
			Debug::MsgBoxAssert("해쉬맵에 이미 동일한 키가 있습니다.");
			return false;	
		}

		if (CurNode->NextPtr == nullptr)
		{
			HashNode* NewNode = new HashNode();
			NewNode->ItemPtr = ItemPtr;
			NewNode->Key = _Key;

			CurNode->NextPtr = NewNode;

			ElementCount++;
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

		if (CurNode->NextPtr == nullptr)
		{
			return nullptr;
		}
		CurNode = CurNode->NextPtr;
	}

	return CurNode->ItemPtr;
}

UINT EngineHashMap::Count()
{
	return ElementCount;
}

void EngineHashMap::GoFirst()
{
	for (UINT i = 0; i < ArraySize; i++)
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
	if (Header->NextPtr != nullptr)
	{
		Header = Header->NextPtr;
		return;
	}

	while (true)
	{
		CurIndex++;
		Header = &Array[CurIndex];

		if (CurIndex >= ArraySize)
		{
			return;
		}

		if (Header->Key != nullptr)
		{
			return;
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

bool EngineIntHashMap::Add(UINT _Key, void* ItemPtr)
{
	if (Array == nullptr)
	{
		Array = new IntHashNode[ArraySize];
	}

	UINT Index = Hash(_Key);

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

void* EngineIntHashMap::Get(UINT _Key)
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
	for (UINT i = 0; i < ArraySize; i++)
	{
		if (Array[i].Key != -1)
		{
			CurIndex = i;
			Header = &Array[CurIndex];
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
		CurIndex++;
		Header = &Array[CurIndex];

		if (CurIndex >= ArraySize)
		{
			return;
		}

		if (Header->Key != -1)
		{
			break;
		}
	}
}

void* EngineIntHashMap::GetCurItem() const
{
	return Header->ItemPtr;
}

UINT EngineIntHashMap::Hash(UINT _Key) const
{
	int Result = 0;

	if (_Key > ArraySize - 1)
	{
		Result = _Key % ArraySize;
	}
	else
	{
		Result = _Key;
	}

	return Result;
}
