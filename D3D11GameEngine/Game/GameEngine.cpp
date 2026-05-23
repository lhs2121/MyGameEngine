#include "pch.h"
#include "GameEngine.h"

void GameEngine::Start(const char* szTitle, float x, float y, float width, float height, HINSTANCE hInstance)
{
	CreateRenderer(&m_pRenderer);

	CreateWindowObject(&m_pWindowObject);
	m_pWindowObject->Initialize(szTitle, x, y, width, height, hInstance, this);

	m_pRenderer->Initialize((UINT)m_pWindowObject->GetWidth(), (UINT)m_pWindowObject->GetHeight(), *m_pWindowObject->GetHWND());

	CreateTimeObject(&m_pTimeObject);
	m_pTimeObject->Initialize();

	CreateInputObject(&m_pInputObject);
	m_pInputObject->Initailize();

	m_pRenderer->LoadTexture(L"Test.png");

	m_blocks.resize(m_blockWidth * m_blockHeight);
	for (int y = 0; y < m_blockHeight; ++y)
	{
		for (int x = 0; x < m_blockWidth; ++x)
		{
			BlockTile& tile = m_blocks[y * m_blockWidth + x];
			tile.tileIndex = 0;
			tile.visible = y >= m_blockHeight / 2 ? 1 : 0;
		}
	}

	m_pTimeObject->CountStart();
	m_pWindowObject->MessageLoop();
}

void GameEngine::EngineUpdate()
{
	float deltaTime = m_pTimeObject->CountEnd();
	m_pTimeObject->CountStart();
	(void)deltaTime;

	m_pInputObject->UpdateKeyStates();
	m_pRenderer->BeginFrame();

	BlockGridDesc gridDesc;
	gridDesc.textureFile = L"Test.png";
	gridDesc.tiles = m_blocks.data();
	gridDesc.width = m_blockWidth;
	gridDesc.height = m_blockHeight;
	gridDesc.atlasColumns = 1;
	gridDesc.atlasRows = 1;
	gridDesc.tileSize = 16.0f;
	gridDesc.originX = -512.0f;
	gridDesc.originY = 128.0f;

	m_pRenderer->DrawBlockGrid(gridDesc);

	m_pRenderer->EndFrame();
}

void GameEngine::EngineRelease()
{
	DeleteInputObject(m_pInputObject);
	DeleteRenderer(m_pRenderer);
	DeleteTimeObject(m_pTimeObject);
	DeleteWindowObject(m_pWindowObject);
}
