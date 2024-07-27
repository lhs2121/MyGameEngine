#pragma once
#include "D3D11API.h"

class EngineIndexBuffer : public IEngineIndexBuffer
{
public:
	EngineIndexBuffer();
	~EngineIndexBuffer();

	void Setting(UINT* Indices, int IndexSize) override;
	void IntoPipeLine() override;
	UINT GetIndexCount() override { return IndexCount; };

private:
	void SetDevice(ID3D11Device* _DevicePtr) override { DevicePtr = _DevicePtr; }
	void SetContext(ID3D11DeviceContext* _ContextPtr) override { ContextPtr = _ContextPtr; }

	ID3D11Device*        DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;

	ID3D11Buffer*        BufferPtr;

	UINT                 IndexCount;
	UINT                 Strides;
	UINT                 Offsets;
};