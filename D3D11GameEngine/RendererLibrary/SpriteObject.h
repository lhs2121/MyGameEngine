#pragma once
#include "IRenderer.h"
#include "ConstantBuffer.h"

struct SpriteData
{
	float2 ratio = { 1.0f, 1.0f };
	float2 offset = { 0.0f, 0.0f };
};

class CMesh;
class CMaterial;
class CRenderer;
class CSpriteObject : public ISpriteObject
{
public:
	CSpriteObject();
	~CSpriteObject();
	void CreateAnimation(const WCHAR* wszTexName, int countX, int countY, float interTime = 0.3f) override;
	void Update(float deltaTime) override; 
	void Draw(ID3D11DeviceContext* pDeviceContext);
	CRenderer* m_pRenderer;
	CMesh* m_pMesh;
	CMaterial* m_pMaterial;

	CConstantBuffer* m_pConstantBuffer_transform;
	CConstantBuffer* m_pConstantBuffer_spriteData;
	SpriteData m_curSpriteData;

	float m_interTime;
	float m_curTime = 0.0f;
	int m_curFrame = 0;
	int m_curSpriteX = 0;
	int m_curSpriteY = 0;
	int m_maxSpriteX;
	int m_maxSpriteY;
	
	std::vector<std::vector<SpriteData>> m_spriteDataList;
};