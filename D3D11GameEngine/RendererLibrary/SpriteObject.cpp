#include "pch.h"
#include "SpriteObject.h"
#include "Mesh.h"
#include "Material.h"
#include "Renderer.h"

CSpriteObject::~CSpriteObject()
{
	if(m_pConstantBuffer_transform)
		delete m_pConstantBuffer_transform;

	if (m_pConstantBuffer_spriteData)
		delete m_pConstantBuffer_spriteData;
}

void CSpriteObject::CreateAnimation(int countX, int countY, float interTime)
{
	m_spriteDataList.resize(countY);
	for (int y = 0; y < countY; y++)
	{
		m_spriteDataList[y].resize(countX);
		for (int x = 0; x < countX; x++)
		{
			float2 fIndex = { (float)x,(float)y };
			float2 ratio = { 1 / (float)countX , 1 / (float)countY };
			float2 offset = ratio * fIndex;
			m_spriteDataList[y][x].ratio = ratio;
			m_spriteDataList[y][x].offset = offset;
		}
	}

	m_curSpriteData = m_spriteDataList[0][0];
	m_maxSpriteX = countX;
	m_maxSpriteY = countY;
	m_interTime = interTime;
}

void CSpriteObject::UpdateAnimation(float deltaTime)
{
	m_curTime += deltaTime;
	if (m_curTime >= m_interTime)
	{
		if (m_curSpriteX == m_maxSpriteX - 1)
		{
			if (m_curSpriteY == m_maxSpriteY - 1)
			{
				m_curSpriteX = 0;
				m_curSpriteY = 0;
				m_curFrame = 0;
				goto asdf;
			}

			m_curSpriteX = 0;
			m_curSpriteY += 1;
		}
		else
			m_curSpriteX += 1;

		m_curFrame += 1;
		m_curTime = 0.0f;
	}

asdf:
	m_curSpriteData = m_spriteDataList[m_curSpriteY][m_curSpriteX];
}

void CSpriteObject::Draw(ID3D11DeviceContext* pDeviceContext)
{
	m_pConstantBuffer_transform->Draw(pDeviceContext);
	m_pConstantBuffer_spriteData->Draw(pDeviceContext);
}
