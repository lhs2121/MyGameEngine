#pragma once

class EngineVector
{
public:
	void Init(int _Size, int _MaxCount);
	unsigned int GetCount();
	void push_back(void* _Element);
	void* operator[](unsigned int index);

	unsigned int Size = 0;
	unsigned int Count = 0;
	void* Header = nullptr;
	void* Array = nullptr;
};