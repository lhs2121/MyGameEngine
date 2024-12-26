#pragma once
#include "Interface.h"
#include "Scene.h"
#include <unordered_map>

class Engine : public IEngine
{
public:
	template<typename T>
	T* CreateScene(const char* _name)
	{
		Scene* newScene = new T();
		newScene->m_pRenderer = m_pRenderer;
		newScene->m_pInputObject = m_pInputObject;
		newScene->SetName(_name);
		newScene->Awake();

		m_sceneMap.insert({ _name,newScene });

		return (T*)newScene;
	}
	void LoadScene(const char* _name);
	void EngineStart(const char* szTitle, float x, float y, float width, float height, HINSTANCE hInstance, Initializer* pGameInit) override;
	void EngineUpdate() override;
	void EngineRelease() override;

private:
	float m_interTime;
	UINT m_maxFps = 155;
	bool m_bFpsLimited = false;
	Scene* m_pCurScene;
	IRenderer* m_pRenderer;
	ITimeObject* m_pTimeObject;
	IWindowObject* m_pWindowObject;
	IInputObject* m_pInputObject;
	std::unordered_map<const char*, Scene*> m_sceneMap;
};
