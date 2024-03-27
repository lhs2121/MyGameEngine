#pragma once
#include "DirectResource.h"

class EngineVertexBuffer : public DirectResource
{
	friend class EngineRenderer;
public:
	// constrcuter destructer
	EngineVertexBuffer();
	EngineVertexBuffer(UINT _StartSlot, UINT _NumBuffers, ID3D11Buffer* _VertexBufferPtr, UINT _Strides, UINT _Offsets) :
		StartSlot(_StartSlot), NumBuffers(_NumBuffers), VertexBufferPtr(_VertexBufferPtr), Strides(_Strides), Offsets(_Offsets)
	{

	}
	~EngineVertexBuffer();

	// delete Function
	EngineVertexBuffer(const EngineVertexBuffer& _Other) = delete;
	EngineVertexBuffer(EngineVertexBuffer&& _Other) noexcept = delete;
	EngineVertexBuffer& operator=(const EngineVertexBuffer& _Other) = delete;
	EngineVertexBuffer& operator=(EngineVertexBuffer&& _Other) noexcept = delete;

	void SetResource(UINT _StartSlot, UINT _NumBuffers, ID3D11Buffer* _VertexBufferPtr, UINT _Strides, UINT _Offsets)
	{
		StartSlot = _StartSlot;
		NumBuffers = _NumBuffers;
		VertexBufferPtr = _VertexBufferPtr;
		Strides = _Strides;
		Offsets = _Offsets;
	}

private:
	UINT StartSlot;
	UINT NumBuffers;
	ID3D11Buffer* VertexBufferPtr;
	UINT Strides;
	UINT Offsets;

};