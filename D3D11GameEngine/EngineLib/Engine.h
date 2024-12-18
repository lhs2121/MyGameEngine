#pragma once
#include "EngineAPI.h"
#include "RendererLibrary/IRenderer.h"
#include <WindowsLibrary/interface.h>
#include "Scene.h"

class Engine : public IEngine
{
public:
	template<typename T>
	T* CreateScene(const char* _name)
	{
		Scene* newScene = new T();
		newScene->m_pRenderer = m_pRenderer;
		newScene->SetName(_name);
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
	IRenderer* m_pRenderer;
	ITime* mainTime = nullptr;
	IWindowObject* m_pWindowObject = nullptr;
	std::unordered_map<const char*, Scene*> allScene;
};
