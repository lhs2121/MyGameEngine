#pragma once
#include "EngineD3DInterface.h"

class EngineConstantBuffer : public IEngineConstantBuffer
{
public:
	// constrcuter destructer
	EngineConstantBuffer();
	~EngineConstantBuffer();

	// delete Function
	EngineConstantBuffer(const EngineConstantBuffer& _Other) = delete;
	EngineConstantBuffer(EngineConstantBuffer&& _Other) noexcept = delete;
	EngineConstantBuffer& operator=(const EngineConstantBuffer& _Other) = delete;
	EngineConstantBuffer& operator=(EngineConstantBuffer&& _Other) noexcept = delete;

	void Setting(D3D11_BUFFER_DESC Desc, void* _DataPtr, int _DataSize) override;
	void Release() override;
	void IntoPipeLine(ShaderType _Type) override;

	void SetDevicePtr(EngineDevice* _DevicePtr)
	{
		DevicePtr = _DevicePtr;
	}

	int DataSize;
	void* DataPtr = nullptr;
	EngineDevice* DevicePtr = nullptr;
	ID3D11Buffer* BufferPtr = nullptr;
};