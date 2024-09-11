#include "Pre.h"
#include <BaseLib/BaseAPI.h>
#include <MediaLib/MediaAPI.h>
#include "Engine.h"
#include "Scene.h"
#include "Naming.h"
#include "Initializer.h"

void Engine::LoadScene(const char* _name)
{
	if (allScene.end() != allScene.find(_name))
	{
		pCurScene = allScene[_name];
		pCurScene->AllGameObjectStart();
	}
}

void Engine::EngineStart(const char* _windowTitle, float _windowPosX, float _windowPosY, float _windowSizeX, float _windowSizeY, HINSTANCE _hInstance, Initializer* pGameInit)
{
	Naming::Create();

	CreateEngineWindow(&mainWindow);
	mainWindow->Init(_windowTitle, { _windowPosX ,_windowPosY }, { _windowSizeX ,_windowSizeY }, _hInstance, this);

	
	CreateDevice(&mainDevice);
	mainDevice->Init(mainWindow->GethWnd(), { _windowSizeX ,_windowSizeY });
	mainDevice->InitMesh();
	mainDevice->InitMaterial();

	CreateEngineTime(&mainTime);
	mainTime->Init();

	CreateEngineInput(&mainInput);
	mainInput->Init();

	pGameInit->CreateAllScene(this);

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
	
	Naming::Delete();
	DeleteEngineTime(mainTime);
	DeleteEngineInput(mainInput);
	DeleteDevice(mainDevice);
	DeleteEngineWindow(mainWindow);
 	Resource::DeleteAllResource();
	EngineString::DeleteAllStringPool();
}



