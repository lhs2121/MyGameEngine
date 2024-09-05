#pragma once
#include "D3D11API.h"

class IndexBuffer : public IIndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	void Setting( UINT* Indices, int IndexSize) override;
	void IntoPipeline() override;

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
	UINT                 IndexCount;
private:
	ID3D11Buffer*        BufferPtr;
	UINT                 Strides;
	UINT                 Offsets;
};