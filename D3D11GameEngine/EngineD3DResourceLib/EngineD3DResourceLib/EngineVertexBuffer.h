#pragma once
#include "IEngineD3D11.h"

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

	void Setting(void* pVertices, int VertexFormatSize, int VertexSize) override;
	void Release() override;
	void IntoPipeLine() override;
	void SetDevicePtr(EngineDevice* _DevicePtr)
	{
		DevicePtr = _DevicePtr;
	}

	EngineDevice* DevicePtr;
	ID3D11Buffer* BufferPtr;
	UINT Strides;
	UINT Offsets;
};