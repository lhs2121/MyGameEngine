#pragma once
#include "Interface.h"
#include "GameObject.h"

class Engine : public IEngine
{
public:
	void EngineStart(const char* szTitle, float x, float y, float width, float height, HINSTANCE hInstance) override;
	void EngineUpdate() override;
	void EngineRelease() override;

	GameObject* CreateGameObject();
	void UpdateGameObjects(float deltaTime);

private:
	float m_interTime;
	UINT m_maxFps = 40;
	bool m_bFpsLimited = false;

	IRenderer* m_pRenderer = nullptr;
	IInputObject* m_pInputObject = nullptr;
	ITimeObject* m_pTimeObject = nullptr;
	IWindowObject* m_pWindowObject = nullptr;

	std::list<GameObject*> m_gameObjectList;
};
