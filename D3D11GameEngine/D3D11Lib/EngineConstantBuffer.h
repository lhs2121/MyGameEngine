#pragma once
#include "D3D11API.h"

class EngineConstantBuffer : public IEngineConstantBuffer
{
public:
	EngineConstantBuffer();
	~EngineConstantBuffer();

	void Setting(D3D11_BUFFER_DESC Desc, void* _DataPtr, int _DataSize) override;
	void IntoPipeline(ShaderType _Type, int SlotNum = 0) override;

private:
	void SetDevice(ID3D11Device* _DevicePtr) override { DevicePtr = _DevicePtr; }
	void SetContext(ID3D11DeviceContext* _ContextPtr) override { ContextPtr = _ContextPtr; }

	int DataSize;
	void* DataPtr = nullptr;
	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
	ID3D11Buffer* BufferPtr = nullptr;
};