#include "Pre.h"
#include "interface.h"
#include "EngineInput.h"

void Input::Create()
{
	if (EngineInput::mainInput != nullptr)
	{
		Debug::MsgBoxAssert("이미 만들어진 인풋클래스가 있습니다");
	}

	EngineInput* input = new EngineInput();
	input->Init();
}

void Input::Delete()
{
	delete EngineInput::mainInput;
}

void Input::UpdateKeyStates()
{
	return EngineInput::mainInput->UpdateKeyStates();
}

bool Input::IsDown(int _key, void* pUser)
{
	return  EngineInput::mainInput->IsDown(_key, pUser);
}

bool Input::IsPress(int _key, void* pUser)
{
	return  EngineInput::mainInput->IsPress(_key, pUser);
}

bool Input::IsUp(int _key, void* pUser)
{
	return  EngineInput::mainInput->IsUp(_key, pUser);
}

bool Input::IsFree(int _key, void* pUser)
{
	return  EngineInput::mainInput->IsFree(_key, pUser);
}

void Input::AddUser(void* pUser)
{
	return  EngineInput::mainInput->AddUser(pUser);
}
