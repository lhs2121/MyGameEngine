#include "pch.h"
#include "Engine.h"
#include <string>

void Engine::LoadScene(const char* _name)
{
	if (m_sceneMap.end() != m_sceneMap.find(_name))
	{
		if (m_pCurScene != nullptr)
		{
			m_pCurScene->AllEnd();
		}

		m_pCurScene = m_sceneMap[_name];
		m_pCurScene->AllStart();
	}
}

void Engine::EngineStart(const char* szTitle, float x, float y, float width, float height, HINSTANCE hInstance, Initializer* pGameInit)
{
	CreateRenderer(&m_pRenderer);

	CreateWindowObject(&m_pWindowObject);
	m_pWindowObject->Initialize(szTitle, x, y, width, height, hInstance, this);

	m_pRenderer->Initialize((UINT)m_pWindowObject->GetWidth(), (UINT)m_pWindowObject->GetHeight(), *m_pWindowObject->GetHWND());

	CreateTimeObject(&m_pTimeObject);
	m_pTimeObject->Initialize();

	CreateInputObject(&m_pInputObject);
	m_pInputObject->Initailize();

	pGameInit->CreateAllScene(this);

	m_pTimeObject->CountStart();

	m_interTime = 1.0f / m_maxFps;
	m_pWindowObject->MessageLoop();
}

void Engine::EngineUpdate()
{
	if (!m_pCurScene)
		return;

	float deltaTime = m_pTimeObject->CountEnd();
	m_pTimeObject->CountStart();

	static float sum = 0;
	sum += deltaTime;
	if (sum >= (1.0f/155.0f)) // 155fps ����
	{
		sum = 0.0f;
	}
	else
	{
		return;
	}

	m_pCurScene->CheckDeath();
	m_pInputObject->UpdateKeyStates();
	m_pRenderer->StartRender();
	m_pCurScene->AllCollisionUpdate();
	m_pCurScene->AllUpdate(deltaTime);
	m_pRenderer->EndRender();
}

void Engine::EngineRelease()
{
	for (auto& pair : m_sceneMap)
	{
		Scene* scene = pair.second;
		delete scene;
	}
	m_sceneMap.clear();
	
	DeleteInputObject(m_pInputObject);
	DeleteRenderer(m_pRenderer);
	DeleteTimeObject(m_pTimeObject);
	DeleteWindowObject(m_pWindowObject);
}


