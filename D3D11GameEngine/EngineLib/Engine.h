#pragma once
#include "EngineAPI.h"
#include "Scene.h"

struct IGameStarter;
class  Engine : public IEngine
{
public:
	template<typename T>
	T* CreateScene(const char* _name)
	{
		Scene* newScene = new T();
		newScene->SetName(_name);
		newScene->SetMainObject(mainInput, mainWindow, mainDevice);
		newScene->CreateCamera();
		newScene->Awake();

		allScene.insert({ _name,newScene });

		return (T*)newScene;
	}
	void LoadScene(const char* _name);
	void EngineStart(const char* _windowTitle, float4 _windowPos, float4 _windowSize, HINSTANCE _hInstance) override;
	void EngineUpdate() override;
	void EngineRelease() override;

private:
	IGameStarter* pGameStarter;
	Scene* pCurScene;
	std::unordered_map<const char*, Scene*> allScene;

	IEngineTime* mainTime = nullptr;
	IEngineWindow* mainWindow = nullptr;
	IEngineInput* mainInput = nullptr;
	IDevice* mainDevice = nullptr;
	 

};
