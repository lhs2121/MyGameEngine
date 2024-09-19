#pragma once
#include "EngineAPI.h"
#include "Scene.h"

class  Engine : public IEngine
{
public:
	template<typename T>
	T* CreateScene(const char* _name)
	{
		Scene* newScene = new T();
		newScene->SetName(_name);
		newScene->CreateCamera();
		newScene->Awake();

		allScene.insert({ _name,newScene });

		return (T*)newScene;
	}
	void LoadScene(const char* _name);
	void EngineStart(const char* _windowTitle, float _windowPosX, float _windowPosY, float _windowSizeX, float _windowSizeY, HINSTANCE _hInstance, Initializer* pGameInit) override;
	void EngineUpdate() override;
	void EngineRelease() override;


private:
	Scene* pCurScene;
	std::unordered_map<const char*, Scene*> allScene;

	ITime* mainTime = nullptr;
};
