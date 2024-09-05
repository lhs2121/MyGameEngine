#pragma once
#include "D3D11API.h"

class ConstantBuffer : public IConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	void Setting( void* _DataPtr, int _sizeofData) override;
	void IntoPipeline(ShaderType _Type, int SlotNum = 0) override;

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
private:
	int DataSize;
	void* DataPtr = nullptr;
	ID3D11Buffer* BufferPtr = nullptr;
};