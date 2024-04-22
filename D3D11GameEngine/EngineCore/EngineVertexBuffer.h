#pragma once
#include "EngineD3DResource.h"

struct VERTEX_POS
{
	float4 Pos;
};

struct VERTEX_POS_COLOR
{
	float4 Pos;
	float4 Color;
};
struct VERTEX_POSTEXCOORD
{
	float4 Pos;
	float4 TexCoord;
};

class EngineVertexBuffer : public EngineD3DResource<EngineVertexBuffer>
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

	void CreateResource(float4* Vertices, int VertexSize);
	void CreateResource(VERTEX_POS_COLOR* Vertices, int VertexSize);
	void IntoPipeLine() override;

private:
	ID3D11Buffer* BufferPtr;
	UINT Strides;
	UINT Offsets;
};