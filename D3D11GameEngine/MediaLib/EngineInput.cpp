#include "Pre.h"
#include "EngineInput.h"

EngineInput::EngineInput()
{
	Users.reserve(100);
}

EngineInput::~EngineInput()
{
	AllKey.GoFirst();
	for (size_t i = 0; i < AllKey.Count(); i++)
	{
		EngineKey* CurKey = (EngineKey*)AllKey.GetCurItem();
		delete CurKey;

		AllKey.GoNext();
	}
}

void EngineInput::Init()
{
	CreateKey(VK_LBUTTON);
	CreateKey(VK_RBUTTON);
	CreateKey(VK_CANCEL);
	CreateKey(VK_MBUTTON);
	CreateKey(VK_XBUTTON1);
	CreateKey(VK_XBUTTON2);

	CreateKey(VK_BACK);
	CreateKey(VK_TAB);

	CreateKey(VK_RETURN);
	CreateKey(VK_SHIFT);
	CreateKey(VK_CONTROL);
	CreateKey(VK_MENU);
	CreateKey(VK_PAUSE);
	CreateKey(VK_CAPITAL);
	CreateKey(VK_HANGEUL);

	CreateKey(VK_ESCAPE);
	CreateKey(VK_SPACE);
	CreateKey(VK_PRIOR);
	CreateKey(VK_NEXT);
	CreateKey(VK_END);
	CreateKey(VK_HOME);
	CreateKey(VK_LEFT);
	CreateKey(VK_UP);
	CreateKey(VK_RIGHT);
	CreateKey(VK_DOWN);
	CreateKey(VK_SNAPSHOT);
	CreateKey(VK_INSERT);
	CreateKey(VK_DELETE);

	CreateKey(0x30); // 0 
	CreateKey(0x31); // 1
	CreateKey(0x32); // 2
	CreateKey(0x33); // 3 
	CreateKey(0x34); // 4
	CreateKey(0x35); // 5
	CreateKey(0x36); // 6
	CreateKey(0x37); // 7
	CreateKey(0x38); // 8
	CreateKey(0x39); // 9

	CreateKey(0x41); // A
	CreateKey(0x42); // B
	CreateKey(0x43); // C
	CreateKey(0x44); // D
	CreateKey(0x45); // E 
	CreateKey(0x46); // F
	CreateKey(0x47); // G
	CreateKey(0x48); // H
	CreateKey(0x49); // I
	CreateKey(0x4A); // J
	CreateKey(0x4B); // K
	CreateKey(0x4C); // L
	CreateKey(0x4D); // M
	CreateKey(0x4E); // N
	CreateKey(0x4F); // O
	CreateKey(0x50); // P
	CreateKey(0x51); // Q
	CreateKey(0x52); // R 
	CreateKey(0x53); // S
	CreateKey(0x54); // T
	CreateKey(0x55); // U
	CreateKey(0x56); // V
	CreateKey(0x57); // W
	CreateKey(0x58); // X
	CreateKey(0x59); // Y
	CreateKey(0x5A); // Z

	CreateKey(VK_LWIN);
	CreateKey(VK_RWIN);
	CreateKey(VK_NUMPAD0);
	CreateKey(VK_NUMPAD1);
	CreateKey(VK_NUMPAD2);
	CreateKey(VK_NUMPAD3);
	CreateKey(VK_NUMPAD4);
	CreateKey(VK_NUMPAD5);
	CreateKey(VK_NUMPAD6);
	CreateKey(VK_NUMPAD7);
	CreateKey(VK_NUMPAD8);
	CreateKey(VK_NUMPAD9);

	CreateKey(VK_MULTIPLY);
	CreateKey(VK_ADD);
	CreateKey(VK_SEPARATOR);
	CreateKey(VK_SUBTRACT);
	CreateKey(VK_DECIMAL);
	CreateKey(VK_DIVIDE);

	CreateKey(VK_F1);
	CreateKey(VK_F2);
	CreateKey(VK_F3);
	CreateKey(VK_F4);
	CreateKey(VK_F5);
	CreateKey(VK_F6);
	CreateKey(VK_F7);
	CreateKey(VK_F8);
	CreateKey(VK_F9);
	CreateKey(VK_F10);
	CreateKey(VK_F11);
	CreateKey(VK_F12);

	CreateKey(VK_NUMLOCK);
	CreateKey(VK_SCROLL);
	CreateKey(VK_LSHIFT);
	CreateKey(VK_RSHIFT);
	CreateKey(VK_LCONTROL);
	CreateKey(VK_RCONTROL);
	CreateKey(VK_LMENU);
	CreateKey(VK_RMENU);
	CreateKey(VK_VOLUME_MUTE);
	CreateKey(VK_VOLUME_DOWN);
	CreateKey(VK_VOLUME_UP);

	CreateKey(VK_OEM_1);
	CreateKey(VK_OEM_PLUS);
	CreateKey(VK_OEM_COMMA);
	CreateKey(VK_OEM_MINUS);
	CreateKey(VK_OEM_PERIOD);
	CreateKey(VK_OEM_2);
	CreateKey(VK_OEM_3);
	CreateKey(VK_OEM_4);
	CreateKey(VK_OEM_5);
	CreateKey(VK_OEM_6);
}

void EngineInput::CreateKey(int KeyCode)
{
	EngineKey* NewKey = new EngineKey();
	NewKey->KeyCode = KeyCode;
	AllKey.Add(KeyCode, NewKey);
}

void EngineInput::UpdateKeyStates()
{
	AllKey.GoFirst();
	for (size_t i = 0; i < AllKey.Count(); i++)
	{
		EngineKey* Key = (EngineKey*)AllKey.GetCurItem();
		SHORT State = GetAsyncKeyState(Key->KeyCode);

		if (State == 0) // 안눌렸을때
		{
			if (Key->IsDown || Key->IsPress) // 이전에 눌러져있었다면 Up
			{	   
				Key->IsDown = false;
				Key->IsPress = false;
				Key->IsUp = true;
				Key->IsFree = false;

				AllKey.GoNext();
				continue;
			}

			// 아니라면 Free
			Key->IsDown = false;
			Key->IsPress = false;
			Key->IsUp = false;
			Key->IsFree = true;

			AllKey.GoNext();
			continue;
		}
		else
		{
			if (Key->IsDown || Key->IsPress) // 이전에 눌러져있다면 Press
			{
				Key->IsDown = false;
				Key->IsPress = true;
				Key->IsUp = false;
				Key->IsFree = false;

				AllKey.GoNext();
				continue;
			}

			// 아니라면 Down
			Key->IsDown = true;
			Key->IsPress = false;
			Key->IsUp = false;
			Key->IsFree = false;

			AllKey.GoNext();
			continue;
		}
	}
}

bool EngineInput::IsDown(int KeyCode, void* _UserPtr)
{
	bool IsUser = false;
	for (void* UserPtr : Users)
	{
		if (UserPtr == _UserPtr)
		{
			IsUser = true;
			break;
		}
	}

	if (IsUser == false)
	{
		return false;
	}

	return ((EngineKey*)(AllKey.Get(KeyCode)))->IsDown;
	
}
bool EngineInput::IsPress(int KeyCode, void* _UserPtr)
{
	bool IsUser = false;
	for (void* UserPtr : Users)
	{
		if (UserPtr == _UserPtr)
		{
			IsUser = true;
			break;
		}
	}

	if (IsUser == false)
	{
		return false;
	}

	return ((EngineKey*)(AllKey.Get(KeyCode)))->IsPress;
}
bool EngineInput::IsUp(int KeyCode, void* _UserPtr)
{
	bool IsUser = false;
	for (void* UserPtr : Users)
	{
		if (UserPtr == _UserPtr)
		{
			IsUser = true;
			break;
		}
	}

	if (IsUser == false)
	{
		return false;
	}

	return ((EngineKey*)(AllKey.Get(KeyCode)))->IsUp;
}
bool EngineInput::IsFree(int KeyCode, void* _UserPtr)
{
	bool IsUser = false;
	for (void* UserPtr : Users)
	{
		if (UserPtr == _UserPtr)
		{
			IsUser = true;
			break;
		}
	}

	if (IsUser == false)
	{
		return false;
	}

	return ((EngineKey*)(AllKey.Get(KeyCode)))->IsFree;
}

void EngineInput::AddUser(void* _UserPtr)
{
	Users.push_back(_UserPtr);
}
