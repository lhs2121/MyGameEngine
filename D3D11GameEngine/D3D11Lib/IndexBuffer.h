#pragma once
#include "D3D11API.h"

class IndexBuffer : public IIndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	void Setting(ID3D11Device* DevicePtr, UINT* Indices, int IndexSize) override;
	void IntoPipeline(ID3D11DeviceContext* ContextPtr) override;

	UINT                 IndexCount;
private:
	ID3D11Buffer*        BufferPtr;
	UINT                 Strides;
	UINT                 Offsets;
};