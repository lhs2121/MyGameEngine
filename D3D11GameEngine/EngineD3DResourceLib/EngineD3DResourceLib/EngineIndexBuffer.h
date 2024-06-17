#pragma once
#include "EngineD3DInterface.h"

class EngineIndexBuffer : public IEngineIndexBuffer
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

	void Setting(UINT* Indices, int IndexSize) override;
	void Release() override;
	void IntoPipeLine() override;
	void SetDevicePtr(EngineDevice* _DevicePtr)
	{
		DevicePtr = _DevicePtr;
	}
	UINT GetIndexCount() override 
	{
		return IndexCount;
	};

	EngineDevice* DevicePtr;
	ID3D11Buffer* BufferPtr;
	UINT IndexCount;
	UINT Strides;
	UINT Offsets;
};