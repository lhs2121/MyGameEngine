#include "pch.h"
#include "Engine.h"

void Engine::EngineStart(const char* szTitle, float x, float y, float width, float height, HINSTANCE hInstance)
{
	CreateRenderer(&m_pRenderer);

	CreateWindowObject(&m_pWindowObject);
	m_pWindowObject->Initialize(szTitle, x, y, width, height, hInstance, this);

	m_pRenderer->Initialize((UINT)m_pWindowObject->GetWidth(), (UINT)m_pWindowObject->GetHeight(), *m_pWindowObject->GetHWND());

	CreateTimeObject(&m_pTimeObject);
	m_pTimeObject->Initialize();

	CreateInputObject(&m_pInputObject);
	m_pInputObject->Initailize();

	m_pTimeObject->CountStart();

	m_interTime = 1.0f / m_maxFps;
	m_pWindowObject->MessageLoop();
}

void Engine::EngineUpdate()
{
	float deltaTime = m_pTimeObject->CountEnd();
	m_pTimeObject->CountStart();


	m_pInputObject->UpdateKeyStates();
	m_pRenderer->StartRender();
	UpdateGameObjects(deltaTime);

	m_pRenderer->EndRender();
}

void Engine::EngineRelease()
{
	DeleteInputObject(m_pInputObject);
	DeleteRenderer(m_pRenderer);
	DeleteTimeObject(m_pTimeObject);
	DeleteWindowObject(m_pWindowObject);
}

GameObject* Engine::CreateGameObject()
{
	GameObject* obj = new GameObject;
	obj->name = "GameObject";
	return obj;
}

void Engine::UpdateGameObjects(float deltaTime)
{
	for (GameObject* obj : m_gameObjectList)
	{
		if (!obj->isUpdate)
			continue;

		if (obj->isTransformChanged)
		{
			obj->TransformUpdate();
			obj->isTransformChanged = false;
		}

		obj->Update(deltaTime);
	}
}