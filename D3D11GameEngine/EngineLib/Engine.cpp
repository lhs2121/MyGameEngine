#include "Pre.h"
#include <BaseLib/BaseAPI.h>
#include <MediaLib/interface.h>
#include "Engine.h"
#include "Scene.h"

void Engine::LoadScene(const char* _name)
{
	if (allScene.end() != allScene.find(_name))
	{
		if (pCurScene != nullptr)
		{
			pCurScene->AllEnd();
		}
		

		pCurScene = allScene[_name];
		pCurScene->AllStart();
	}
}

void Engine::EngineStart(const char* _windowTitle, float _windowPosX, float _windowPosY, float _windowSizeX, float _windowSizeY, HINSTANCE _hInstance, Initializer* pGameInit)
{
	CreateRenderer(&m_pRenderer);

	CreateWindowObject(&m_pWindowObject);
	m_pWindowObject->Initialize(_windowTitle, _windowPosX, _windowPosY, _windowSizeX, _windowSizeY, _hInstance, this);

	m_pRenderer->Initialize((UINT)m_pWindowObject->GetWidth(), (UINT)m_pWindowObject->GetHeight(), *m_pWindowObject->GetHWND());

	CreateEngineTime(&mainTime);
	mainTime->Init();

	Input::Create();

	pGameInit->CreateAllScene(this);

	mainTime->CountStart();

	m_pWindowObject->MessageLoop();
}

void Engine::EngineUpdate()
{
	if (pCurScene == nullptr)
	{
		return;
	}

	Input::UpdateKeyStates();

	float deltaTime = mainTime->CountEnd();
	mainTime->CountStart();

	pCurScene->CheckDeath();

	m_pRenderer->StartRender();

	pCurScene->AllCollisionUpdate();
	pCurScene->AllUpdate(deltaTime);

	m_pRenderer->EndRender();
}

void Engine::EngineRelease()
{
	for (auto& pair : allScene)
	{
		Scene* scene = pair.second;
		delete scene;
	}
	allScene.clear();
	
	DeleteRenderer(m_pRenderer);
	DeleteEngineTime(mainTime);
	DeleteWindowObject(m_pWindowObject);
	Input::Delete();
}



