#include "Pre.h"
#include <BaseLib/BaseAPI.h>
#include <MediaLib/MediaAPI.h>
#include <GameLib/GameAPI.h>
#include "Engine.h"
#include "Scene.h"

void Engine::LoadScene(const char* _name)
{
	if (allScene.end() != allScene.find(_name))
	{
		pCurScene = allScene[_name];
		pCurScene->AllGameObjectStart();
	}
}

void Engine::EngineStart(const char* _windowTitle, float4 _windowPos, float4 _windowSize, HINSTANCE _hInstance)
{
	CreateEngineWindow(&mainWindow);
	mainWindow->Init(_windowTitle, _windowPos, _windowSize, _hInstance, this);

	
	CreateDevice(&mainDevice);
	mainDevice->Init(mainWindow->GethWnd(), _windowSize);
	mainDevice->InitMesh();
	mainDevice->InitMaterial();

	CreateEngineTime(&mainTime);
	mainTime->Init();

	CreateEngineInput(&mainInput);
	mainInput->Init();

	CreateGameStarter(&pGameStarter);
	pGameStarter->GameStart(this);

	mainTime->CountStart();

	mainWindow->MessageLoop();
}

void Engine::EngineUpdate()
{
	if (pCurScene == nullptr)
	{
		return;
	}

	mainInput->UpdateKeyStates();

	float deltaTime = mainTime->CountEnd();
	mainTime->CountStart();

	pCurScene->Update(deltaTime);
	pCurScene->AllGameObjectUpdate(deltaTime);
	pCurScene->AllCollisionUpdate(deltaTime);

	mainDevice->Clear();

	pCurScene->Render();

	mainDevice->Present();
}

void Engine::EngineRelease()
{
	for (auto& pair : allScene)
	{
		Scene* scene = pair.second;
		delete scene;
	}
	allScene.clear();
	
	DeleteEngineTime(mainTime);
	DeleteEngineInput(mainInput);
	DeleteDevice(mainDevice);
	Resource::DeleteAllResource();
	DeleteEngineWindow(mainWindow);
	DeleteGameStarter(pGameStarter);
	EngineString::DeleteAllStringPool();
}



