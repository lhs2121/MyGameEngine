#pragma once
#include "IEngineD3DRes.h"

class EngineVertexBuffer : public IEngineVertexBuffer
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

	void IntoPipeLine() override;
	void SetDevicePtr(IEngineDevice* pDevice)
	{
		pDevice = pDevice;
	}
	IEngineDevice* m_pDevice;

	ID3D11Buffer* BufferPtr;
	UINT Strides;
	UINT Offsets;
};