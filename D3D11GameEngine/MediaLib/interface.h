#pragma once
#include "Windows.h"

struct IEngine;
namespace Input
{
	MediaAPI void        Create();

	MediaAPI void        Delete();

	extern "C" MediaAPI void        UpdateKeyStates();

	extern "C" MediaAPI bool        IsDown(int _key, void* pUser);

	extern "C" MediaAPI bool        IsPress(int _key, void* pUser);

	extern "C" MediaAPI bool        IsUp(int _key, void* pUser);

	extern "C" MediaAPI bool        IsFree(int _key, void* pUser);

	extern "C" MediaAPI void        AddUser(void* pUser);
}