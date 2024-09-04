#pragma once
#include "D3D11API.h"

class ConstantBuffer : public IConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	void Setting(ID3D11Device* DevicePtr, void* _DataPtr, int _sizeofData) override;
	void IntoPipeline(ID3D11DeviceContext* ContextPtr, ShaderType _Type, int SlotNum = 0) override;

private:
	int DataSize;
	void* DataPtr = nullptr;
	ID3D11Buffer* BufferPtr = nullptr;
};