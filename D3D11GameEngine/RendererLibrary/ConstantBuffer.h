#pragma once
#include "IRenderer.h"

class CConstantBuffer 
{
public:
	~CConstantBuffer();

	void Draw(ID3D11DeviceContext* pDeviceContext);
	void* m_pData = nullptr;
	const char* m_szTargetShader;
	int m_slot = 0;
	UINT m_dataSize;
	ID3D11Buffer* m_pBuffer;
	D3D11_MAPPED_SUBRESOURCE m_subResourece;
};