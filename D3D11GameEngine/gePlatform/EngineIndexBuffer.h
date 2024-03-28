#pragma once
#include "DirectResource.h"

class EngineIndexBuffer : public DirectResource<EngineIndexBuffer>
{
public:
	// constrcuter destructer
	EngineIndexBuffer();
	~EngineIndexBuffer();

	// delete Function
	EngineIndexBuffer(const EngineIndexBuffer& _Other) = delete;
	EngineIndexBuffer(EngineIndexBuffer&& _Other) noexcept = delete;
	EngineIndexBuffer& operator=(const EngineIndexBuffer& _Other) = delete;
	EngineIndexBuffer& operator=(EngineIndexBuffer&& _Other) noexcept = delete;

	void SetResource(UINT* Indices, int IndexSize);
	void IntoPipeLine() override;

private:
	ID3D11Buffer* BufferPtr;
	UINT Strides;
	UINT Offsets;
};