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

	void Release() override;
	UINT GetIndexCount() override 
	{
		return IndexCount;
	};
	void IntoPipeLine() override;
	void SetDevicePtr(ID3D11DeviceContext* pDeviceContext)
	{
		DeviceContext = pDeviceContext;
	}
	ID3D11DeviceContext* DeviceContext;

	ID3D11Buffer* BufferPtr;
	UINT IndexCount;
	UINT Strides;
	UINT Offsets;
};