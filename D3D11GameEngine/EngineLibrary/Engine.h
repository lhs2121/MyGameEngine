#pragma once
#include "Interface.h"
#include "Level.h"
#include <unordered_map>

class Engine : public IEngine
{
public:
	template<typename T>
	T* CreateLevel(const char* _name)
	{
		Level* pLevel = new T();
		pLevel->renderer = m_pRenderer;
		pLevel->input = m_pInputObject;
		pLevel->Awake();

		levelList.insert({ _name,newScene });

		return (T*)newScene;
	}
	void LoadLevel(const char* _name);
	void EngineStart(const char* szTitle, float x, float y, float width, float height, HINSTANCE hInstance, Initializer* pGameInit) override;
	void EngineUpdate() override;
	void EngineRelease() override;

private:
	float m_interTime;
	UINT m_maxFps = 40;
	bool m_bFpsLimited = false;
	Level* m_pCurLevel;
	IRenderer* m_pRenderer;
	ITimeObject* m_pTimeObject;
	IWindowObject* m_pWindowObject;
	IInputObject* m_pInputObject;
	std::unordered_map<const char*, Level*> levelList;
};
