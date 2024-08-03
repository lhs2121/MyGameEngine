#include "Pre.h"
#include "EngineConstantBuffer.h"

EngineConstantBuffer::EngineConstantBuffer()
{
}

EngineConstantBuffer::~EngineConstantBuffer()
{
	if (BufferPtr != nullptr)
	{
		BufferPtr->Release();
		BufferPtr = nullptr;
	}
}

void EngineConstantBuffer::Setting(void* _DataPtr, int _sizeofData)
{
	D3D11_BUFFER_DESC Desc = { 0 };
	Desc.Usage = D3D11_USAGE_DYNAMIC;
	Desc.ByteWidth = _sizeofData;
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Desc.MiscFlags = 0;
	Desc.StructureByteStride = 0;

	DataPtr = _DataPtr;
	DataSize = _sizeofData;
	DevicePtr->CreateBuffer(&Desc, nullptr, &BufferPtr);
}

void EngineConstantBuffer::IntoPipeline(ShaderType _Type, int SlotNum)
{
	D3D11_MAPPED_SUBRESOURCE MappedRes;

	ContextPtr->Map(BufferPtr, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedRes);
	memcpy_s(MappedRes.pData, DataSize, DataPtr, DataSize);

	ContextPtr->Unmap(BufferPtr, 0);

	switch (_Type)
	{
	case ShaderType::VS:
		ContextPtr->VSSetConstantBuffers(SlotNum, 1, &BufferPtr);
		break;
	case ShaderType::PS:
		ContextPtr->PSSetConstantBuffers(SlotNum, 1, &BufferPtr);
		break;
	case ShaderType::CS:
		break;
	case ShaderType::HS:
		break;
	case ShaderType::DS:
		break;
	case ShaderType::GS:
		break;
	default:
		break;
	}
	
}
