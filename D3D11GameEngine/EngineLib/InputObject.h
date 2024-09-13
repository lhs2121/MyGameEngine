#pragma once
#include "Object.h"

class InputObject : public Object
{
public:
	bool GetKeyDown(int _key);
	bool GetKeyPress(int _key);
	bool GetKeyUp(int _key);
	bool GetKeyFree(int _key);
};