#pragma once
#include "DirectResource.h"

class EngineVertexBuffer : public DirectResource<EngineVertexBuffer>
{
public:
	// constrcuter destructer
	EngineVertexBuffer();
	~EngineVertexBuffer();

	// delete Function
	EngineVertexBuffer(const EngineVertexBuffer& _Other) = delete;
	EngineVertexBuffer(EngineVertexBuffer&& _Other) noexcept = delete;
	EngineVertexBuffer& operator=(const EngineVertexBuffer& _Other) = delete;
	EngineVertexBuffer& operator=(EngineVertexBuffer&& _Other) noexcept = delete;

	void SetResource(float4* Vertices, int VertexSize);
	void IntoPipeLine() override;

private:
	ID3D11Buffer* BufferPtr;
	UINT Strides;
	UINT Offsets;
};