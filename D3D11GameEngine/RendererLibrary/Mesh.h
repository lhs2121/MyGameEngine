#pragma once
#include "IRenderer.h"

class CMesh : public IMesh
{
public:
	~CMesh();
	void Draw(ID3D11DeviceContext* pDeviceContext);

	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11Buffer* m_pIndexBuffer = nullptr;

	UINT m_vertexStrides;
	UINT m_indexStrides;
};