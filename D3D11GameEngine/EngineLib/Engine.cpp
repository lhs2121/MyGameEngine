#include "Pre.h"
#include <BaseLib/BaseAPI.h>
#include <MediaLib/MediaAPI.h>
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

	Window::Create(_windowTitle, { _windowPosX ,_windowPosY }, { _windowSizeX ,_windowSizeY }, _hInstance, this);

	m_pRenderer->Initialize((UINT)Window::GetSizeX(), (UINT)Window::GetSizeY(), *Window::GethWnd());

	CreateEngineTime(&mainTime);
	mainTime->Init();

	Input::Create();

	pGameInit->CreateAllScene(this);

	mainTime->CountStart();

	Window::MessageLoop();
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
	Window::Delete();
	Input::Delete();
}



