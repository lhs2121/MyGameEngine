#pragma once
#include "Interface.h"
#include "ConstantBuffer.h"

class CMesh;
class CMaterial;
class CRenderer;
class CSpriteObject : public ISpriteObject
{
public:
	~CSpriteObject();
	void CreateAnimation(int countX, int countY, float interTime);
	void UpdateAnimation(float deltaTime) override; 
	void Draw(ID3D11DeviceContext* pDeviceContext);
	CConstantBuffer* m_pConstantBuffer_transform;
	CConstantBuffer* m_pConstantBuffer_spriteData;
	ID3D11ShaderResourceView* m_pSRV;
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