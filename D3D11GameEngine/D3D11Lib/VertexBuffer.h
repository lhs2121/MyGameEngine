#pragma once
#include "D3D11API.h"

class VertexBuffer : public IVertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void Setting(ID3D11Device* DevicePtr, void* pVertices, int VertexFormatSize, int VertexSize, UINT _SlotNumber) override;
	void IntoPipeline(ID3D11DeviceContext* ContextPtr) override;

	UINT GetSlotNumber() const { return SlotNumber; }
private:
	ID3D11Buffer* BufferPtr;
	UINT Strides;
	UINT Offsets;
	UINT SlotNumber = 0;
};