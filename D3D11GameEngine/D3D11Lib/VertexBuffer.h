#pragma once
#include "D3D11API.h"

class VertexBuffer : public IVertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void Setting(void* pVertices, int _Stride, int _ByteWidth, UINT _SlotNumber = 0) override;
	void IntoPipeline() override;

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
	UINT GetSlotNumber() const { return SlotNumber; }
private:
	ID3D11Buffer* BufferPtr;
	UINT Strides;
	UINT Offsets;
	UINT SlotNumber = 0;
};