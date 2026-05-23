#pragma once
#include <Windows.h>
#include <BaseLibrary/Interface.h>
#include <InputLibrary/Interface.h>
#include <RendererLibrary/Interface.h>
#include <WindowLibrary/Interface.h>
#include <vector>

class GameEngine : public IEngine
{
public:
	void Start(const char* szTitle, float x, float y, float width, float height, HINSTANCE hInstance);
	void EngineUpdate() override;
	void EngineRelease() override;

private:
	IRenderer* m_pRenderer = nullptr;
	ITimeObject* m_pTimeObject = nullptr;
	IWindowObject* m_pWindowObject = nullptr;
	IInputObject* m_pInputObject = nullptr;
	std::vector<BlockTile> m_blocks;
	int m_blockWidth = 64;
	int m_blockHeight = 36;
};
