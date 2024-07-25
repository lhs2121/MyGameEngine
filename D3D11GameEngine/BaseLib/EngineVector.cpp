#include "Pre.h"
#include "EngineVector.h"


void EngineVector::Init(int _Size, int _MaxCount)
{
	Array = malloc(_Size * _MaxCount);
	Size = _Size;
	Header = Array;
}

unsigned int EngineVector::GetCount()
{
	return Count;
}

void EngineVector::push_back(void* _Element)
{
	memcpy(Header, _Element, Size);
	Header = (char*)Header + Size;
}
	
void* EngineVector::operator[](unsigned int index)
{
	void* Return = (char*)Array + (Size * index);
	return Return;
}


