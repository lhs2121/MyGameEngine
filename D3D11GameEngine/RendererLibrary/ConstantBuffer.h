#pragma once
#include "Interface.h"
#include <list>

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