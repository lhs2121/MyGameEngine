#include "Pre.h"
#include "EngineConstantBuffer.h"

EngineConstantBuffer::EngineConstantBuffer()
{
}

EngineConstantBuffer::~EngineConstantBuffer()
{
}

void EngineConstantBuffer::Setting(D3D11_BUFFER_DESC Desc, void* _DataPtr, int _DataSize)
{
	DataPtr = _DataPtr;
	DataSize = _DataSize;
	DevicePtr->GetDevice()->CreateBuffer(&Desc, nullptr, &BufferPtr);
}

void EngineConstantBuffer::Release()
{
	if (BufferPtr != nullptr)
	{
		BufferPtr->Release();
		BufferPtr = nullptr;
	}
}

void EngineConstantBuffer::IntoPipeLine(ShaderType _Type)
{
	D3D11_MAPPED_SUBRESOURCE MappedRes;

	DevicePtr->GetContext()->Map(BufferPtr, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedRes);
	memcpy_s(MappedRes.pData, DataSize, DataPtr, DataSize);

	DevicePtr->GetContext()->Unmap(BufferPtr, 0);

	switch (_Type)
	{
	case ShaderType::VS:
		DevicePtr->GetContext()->VSSetConstantBuffers(0, 1, &BufferPtr);
		break;
	case ShaderType::PS:
		DevicePtr->GetContext()->PSSetConstantBuffers(0, 1, &BufferPtr);
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
