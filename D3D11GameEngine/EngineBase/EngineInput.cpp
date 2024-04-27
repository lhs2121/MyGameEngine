#include "Pre.h"
#include "EngineInput.h"
#include <WinUser.h>
EngineInput::EngineInput()
{
}

EngineInput::~EngineInput()
{
}

void EngineInput::AllKeyInit()
{
	AddKey(VK_LBUTTON);
	AddKey(VK_RBUTTON);
	AddKey(VK_CANCEL);
	AddKey(VK_MBUTTON);
	AddKey(VK_XBUTTON1);
	AddKey(VK_XBUTTON2);

	AddKey(VK_BACK);
	AddKey(VK_TAB);

	AddKey(VK_RETURN);
	AddKey(VK_SHIFT);
	AddKey(VK_CONTROL);
	AddKey(VK_MENU);
	AddKey(VK_PAUSE);
	AddKey(VK_CAPITAL);
	AddKey(VK_KANA);
	AddKey(VK_HANGEUL);
	AddKey(VK_HANGUL);

	AddKey(VK_ESCAPE);
	AddKey(VK_SPACE);
	AddKey(VK_PRIOR);
	AddKey(VK_NEXT);
	AddKey(VK_END);
	AddKey(VK_HOME);
	AddKey(VK_LEFT);
	AddKey(VK_UP);
	AddKey(VK_RIGHT);
	AddKey(VK_DOWN);
	AddKey(VK_SNAPSHOT);
	AddKey(VK_INSERT);
	AddKey(VK_DELETE);

	AddKey(0x30); // 0 
	AddKey(0x31); // 1
	AddKey(0x32); // 2
	AddKey(0x33); // 3 
	AddKey(0x34); // 4
	AddKey(0x35); // 5
	AddKey(0x36); // 6
	AddKey(0x37); // 7
	AddKey(0x38); // 8
	AddKey(0x39); // 9

	AddKey(0x41); // A
	AddKey(0x42); // B
	AddKey(0x43); // C
	AddKey(0x44); // D
	AddKey(0x45); // E 
	AddKey(0x46); // F
	AddKey(0x47); // G
	AddKey(0x48); // H
	AddKey(0x49); // I
	AddKey(0x4A); // J
	AddKey(0x4B); // K
	AddKey(0x4C); // L
	AddKey(0x4D); // M
	AddKey(0x4E); // N
	AddKey(0x4F); // O
	AddKey(0x50); // P
	AddKey(0x51); // Q
	AddKey(0x52); // R 
	AddKey(0x53); // S
	AddKey(0x54); // T
	AddKey(0x55); // U
	AddKey(0x56); // V
	AddKey(0x57); // W
	AddKey(0x58); // X
	AddKey(0x59); // Y
	AddKey(0x5A); // Z

	AddKey(VK_LWIN);
	AddKey(VK_RWIN);
	AddKey(VK_NUMPAD0);
	AddKey(VK_NUMPAD1);
	AddKey(VK_NUMPAD2);
	AddKey(VK_NUMPAD3);
	AddKey(VK_NUMPAD4);
	AddKey(VK_NUMPAD5);
	AddKey(VK_NUMPAD6);
	AddKey(VK_NUMPAD7);
	AddKey(VK_NUMPAD8);
	AddKey(VK_NUMPAD9);

	AddKey(VK_MULTIPLY);
	AddKey(VK_ADD);
	AddKey(VK_SEPARATOR);
	AddKey(VK_SUBTRACT);
	AddKey(VK_DECIMAL);
	AddKey(VK_DIVIDE);

	AddKey(VK_F1);
	AddKey(VK_F2);
	AddKey(VK_F3);
	AddKey(VK_F4);
	AddKey(VK_F5);
	AddKey(VK_F6);
	AddKey(VK_F7);
	AddKey(VK_F8);
	AddKey(VK_F9);
	AddKey(VK_F10);
	AddKey(VK_F11);
	AddKey(VK_F12);

	AddKey(VK_NUMLOCK);
	AddKey(VK_SCROLL);
	AddKey(VK_LSHIFT);
	AddKey(VK_RSHIFT);
	AddKey(VK_LCONTROL);
	AddKey(VK_RCONTROL);
	AddKey(VK_LMENU);
	AddKey(VK_RMENU);
	AddKey(VK_VOLUME_MUTE);
	AddKey(VK_VOLUME_DOWN);
	AddKey(VK_VOLUME_UP);

	AddKey(VK_OEM_1);
	AddKey(VK_OEM_PLUS);
	AddKey(VK_OEM_COMMA);
	AddKey(VK_OEM_MINUS);
	AddKey(VK_OEM_PERIOD);
	AddKey(VK_OEM_2);
	AddKey(VK_OEM_3);
	AddKey(VK_OEM_4);
	AddKey(VK_OEM_5);
	AddKey(VK_OEM_6);

	AddKey(VK_VOLUME_UP);
}

void EngineInput::AddKey(int KeyCode)
{
	EngineKey NewKey;
	NewKey.KeyCode = KeyCode;
	AllKey.push_back(NewKey);
}

void EngineInput::SetAllKeyState()
{
	for (EngineKey& Key : AllKey)
	{
		SHORT State = GetAsyncKeyState(Key.KeyCode);

		if (State == 0) // 안눌렸을때
		{
			if (Key.IsDown || Key.IsPress) // 이전에 눌러져있었다면 Up
			{
				Key.IsDown = false;
				Key.IsPress = false;
				Key.IsUp = true;
				Key.IsFree = false;
				continue;
			}

			// 아니라면 Free
			Key.IsDown = false;
			Key.IsPress = false;
			Key.IsUp = false;
			Key.IsFree = true;
			continue;
		}
		else
		{
			if (Key.IsDown || Key.IsPress) // 이전에 눌러져있다면 Press
			{
				Key.IsDown = false;
				Key.IsPress = true;
				Key.IsUp = false;
				Key.IsFree = false;
				continue;
			}

			// 아니라면 Down
			Key.IsDown = true;
			Key.IsPress = false;
			Key.IsUp = false;
			Key.IsFree = false;
			continue;
		}
	}
}

bool EngineInput::IsDown(int KeyCode)
{
	for (EngineKey& Key : AllKey)
	{
		if (KeyCode == Key.KeyCode)
		{
			return Key.IsDown;
		}
	}

	return false;
}
bool EngineInput::IsPress(int KeyCode)
{
	for (EngineKey& Key : AllKey)
	{
		if (KeyCode == Key.KeyCode)
		{
			return Key.IsPress;
		}
	}

	return false;
}

bool EngineInput::IsUp(int KeyCode)
{
	for (EngineKey& Key : AllKey)
	{
		if (KeyCode == Key.KeyCode)
		{
			return Key.IsUp;
		}
	}

	return false;
}

bool EngineInput::IsFree(int KeyCode)
{
	for (EngineKey& Key : AllKey)
	{
		if (KeyCode == Key.KeyCode)
		{
			return Key.IsFree;
		}
	}

	return false;
}

