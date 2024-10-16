#include "Pre.h"
#include <BaseLib/BaseAPI.h>
#include <MediaLib/MediaAPI.h>
#include "Engine.h"
#include "Scene.h"
#include "Naming.h"

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
	Naming::Create();
	Naming::AddName("Object");
	Naming::AddName("Colider");
	Naming::AddName("Renderer");
	Naming::AddName("DebugRenderer");
	Naming::AddName("SpriteData");

	Window::Create(_windowTitle, { _windowPosX ,_windowPosY }, { _windowSizeX ,_windowSizeY }, _hInstance, this);

	Device::Create(Window::GethWnd(), { _windowSizeX ,_windowSizeY });
	Device::InitMesh();
	Device::InitMaterial();

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

	pCurScene->AllUpdate(deltaTime);
	pCurScene->UpdateQuadTree();

	Device::Clear();

	pCurScene->Render();
	
	Device::Present();


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
	Window::Delete();
	Input::Delete();
 	Resource::DeleteAllResource();
	Device::Delete();
	Naming::Delete();
}



