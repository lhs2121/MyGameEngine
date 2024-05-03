#pragma once
#include "IEngineD3DRes.h"

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

	UINT GetIndexCount() const
	{
		return IndexCount;
	};
	void IntoPipeLine() override;
	void SetDevicePtr(IEngineDevice* pDevice)
	{
		Device = pDevice;
	}
	IEngineDevice* Device;

	ID3D11Buffer* BufferPtr;
	UINT IndexCount;
	UINT Strides;
	UINT Offsets;
};