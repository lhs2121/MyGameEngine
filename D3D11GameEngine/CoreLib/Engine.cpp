#include "Pre.h"
#include <BaseLib/BaseAPI.h>
#include <MediaLib/MediaAPI.h>
#include <D3D11Lib/D3D11API.h>
#include <GameLib/GameAPI.h>
#include "Engine.h"
#include "Level.h"

Level* Engine::CreateLevel(const char* _name, Level* _newLevel)
{
	_newLevel->SetMainObject(mainInput, mainWindow, mainDevice, mainResManager);
	_newLevel->SetName(_name);
	_newLevel->CreateCamera();
	_newLevel->Awake();

	allLevel.insert({ _name, _newLevel });
	return _newLevel;
}

void Engine::ChangeLevel(const char* _name)
{
	if (allLevel.end() != allLevel.find(_name))
	{
		pCurLevel = allLevel[_name];
	}
}

void Engine::EngineStart(const char* _windowTitle, float4 _windowPos, float4 _windowSize, HINSTANCE _hInstance, IGameStarter* _Starter)
{
	CreateEngineWindow(&mainWindow);
	mainWindow->Init(_windowTitle, _windowPos, _windowSize, _hInstance, this);

	CreateResManager(&mainResManager);
	mainResManager->CreateDevice(&mainDevice);

	mainDevice->Init(mainWindow->GethWnd(), _windowSize);
	mainDevice->InitMesh(mainResManager);
	mainDevice->InitMaterial(mainResManager);

	CreateEngineTime(&mainTime);
	mainTime->Init();

	CreateEngineInput(&mainInput);
	mainInput->Init();

	pGameStarter = _Starter;
	pGameStarter->GameStart(this);

	mainTime->CountStart();

	mainWindow->MessageLoop();
}

void Engine::EngineUpdate()
{
	if (pCurLevel == nullptr)
	{
		return;
	}

	mainInput->UpdateKeyStates();

	float deltaTime = mainTime->CountEnd();
	mainTime->CountStart();

	pCurLevel->Update(deltaTime);
	pCurLevel->AllGameObjectUpdate(deltaTime);

	mainDevice->Clear();

	pCurLevel->Render();

	mainDevice->Present();
}

void Engine::EngineRelease()
{
	for (auto& level : allLevel)
	{
		delete level.second;
	}
	allLevel.clear();
	
	DeleteEngineTime(mainTime);
	DeleteEngineInput(mainInput);
	DeleteResManager(mainResManager);
	DeleteEngineWindow(mainWindow);
	EngineString::DeleteAllStringPool();
}



