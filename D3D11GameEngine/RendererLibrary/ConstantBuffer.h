#pragma once
#include "Interface.h"
#include <list>
class Transform
{
public:
	void TransformUpdate();

	void SetScale(CXMVECTOR scale);
	void SetRotation(CXMVECTOR rot);
	void SetPos(CXMVECTOR pos);

	void AddScale(CXMVECTOR scale);
	void AddRotation(CXMVECTOR rot);
	void AddPos(CXMVECTOR pos);

private:
	XMVECTOR m_vecScale;
	XMVECTOR m_vecRotation;
	XMVECTOR m_vecPosition;

	XMVECTOR m_vecQutainon;

	XMMATRIX m_matWorld;
};

class ConstantBuffer 
{
public:
	~ConstantBuffer();

	void Bind(ID3D11DeviceContext* pDeviceContext);

	void* m_pData = nullptr;
	const char* m_szShaderType;
	int m_slot = 0;
	UINT m_dataSize;
	ID3D11Buffer* m_pBuffer;
};