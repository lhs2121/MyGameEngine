#pragma once
#include "D3D11API.h"

class EngineVertexBuffer : public IEngineVertexBuffer
{
public:
	EngineVertexBuffer();
	~EngineVertexBuffer();

	void Setting(void* pVertices, int VertexFormatSize, int VertexSize) override;
	void IntoPipeLine() override;

private:
	void SetDevice(ID3D11Device* _DevicePtr) override { DevicePtr = _DevicePtr; }
	void SetContext(ID3D11DeviceContext* _ContextPtr) override { ContextPtr = _ContextPtr; }

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
	ID3D11Buffer* BufferPtr;
	UINT Strides;
	UINT Offsets;
};